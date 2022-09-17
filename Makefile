# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

include Makefile.headers.mk
include Makefile.tests.mk
include Makefile.lib.mk
include Makefile.sources.mk

HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I$(HEADER_DIR)

RM= rm -rf

NAME= 42sh

.PHONY: all test debug clean fclean re leaks

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(LIB_OBJS) $(OBJS_DEBUG) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(LIB_OBJS) $(OBJS_DEBUG)

leaks: $(NAME)
	export MallocStackLogging=1; leaks --atExit -- ./42sh; unset MallocStackLogging

test: $(OBJS) $(HEADERS) $(TESTS_OBJS) Makefile
	@echo $(TESTS_OBJS)
	$(CC) -o $(NAME)_test $(TESTS_OBJS)

debug: $(NAME)
	$(CC) -g -fsanitize=address -o $(NAME) $(OBJS_DEBUG)

clean:
	$(RM) $(OBJS) $(TESTS_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_test

re: fclean all
