# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

include Makefile.headers.mk
include Makefile.tests.mk
include Makefile.lib.mk
include Makefile.sources.mk

HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -Wconversion -I$(HEADER_DIR) -g -fsanitize=address,undefined
LDFLAGS= -g -fsanitize=address,undefined

RM= rm -rf

NAME= 42sh
MAKEFLAGS += --no-print-directory

# Color codes
COLOR_RESET = \033[0m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_BLUE = \033[34m
COLOR_CYAN = \033[36m

# Count total source files
TOTAL_SRCS := $(words $(OBJS) $(LIB_OBJS))

# Pattern rules with progress indicators
%.o: %.c
	@COMPILED=$$(find . -name "*.o" 2>/dev/null | wc -l | tr -d ' '); \
	echo "$(COLOR_CYAN)[$$(($$COMPILED + 1))/$(TOTAL_SRCS)]$(COLOR_RESET)  $(COLOR_BLUE)CC$(COLOR_RESET)      $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all test production clean fclean re leaks lldb analyze

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(LIB_OBJS) $(OBJS) $(HEADERS) Makefile
	@echo "  $(COLOR_GREEN)LINK$(COLOR_RESET)    $(NAME)"
	@$(CC) $(LDFLAGS) -o $(NAME) $(LIB_OBJS) $(OBJS)

leaks: $(NAME)
	export MallocStackLogging=1; leaks --atExit -- ./42sh; unset MallocStackLogging

test: $(OBJS) $(HEADERS) $(LIB_OBJS) $(TESTS_OBJS) Makefile
	@echo "  $(COLOR_GREEN)LINK$(COLOR_RESET)    $(NAME)_test"
	@$(CC) -o $(NAME)_test $(LIB_OBJS) $(TESTS_OBJS)

production: fclean
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -Wconversion -I$(HEADER_DIR) -O2" LDFLAGS="" $(NAME)
	@echo "$(COLOR_GREEN)Production build complete$(COLOR_RESET) (optimized, no debug symbols)"

analyze:
	@echo "$(COLOR_YELLOW)Running static analysis...$(COLOR_RESET)"
	@$(CC) --analyze $(CFLAGS) $(wildcard src/**/*.c src/*.c lib/**/*.c lib/*.c) 2>&1 | grep -v "0 warnings generated" || true
	@echo "$(COLOR_GREEN)Static analysis complete$(COLOR_RESET)"

clean:
	$(RM) $(OBJS) $(LIB_OBJS) $(TESTS_OBJS)
	@find . -name "*.plist" -type f -delete 2>/dev/null || true

fclean: clean
	$(RM) $(NAME) $(NAME)_test
	@find . -name "*.o" -type f -delete 2>/dev/null || true

re: fclean all
