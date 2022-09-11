# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

include Makefile.lib.mk
include Makefile.sources.mk

HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I$(HEADER_DIR)

RM= rm -rf

NAME= 42sh

.PHONY: all test debug clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(LIB_OBJS) $(OBJS_DEBUG) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(LIB_OBJS) $(OBJS_DEBUG)

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


# # https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

# SRDIR= src/
# HEADER_DIR= includes/

# # READLINE_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/editline
# # EXTERNAL_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/

# # built-in rules
# CC= clang
# CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR) #-I$(EXTERNAL_DIR) -I$(READLINE_DIR)

# RM= rm -rf

# SRCS_RAW=	main lexer/lexer lexer/__debug lexer/get_token_type\
# 			lexer/rules/whitespace lexer/rules/command\
# 			lexer/rules/unknown lexer/rules/operator\
# 			parser/btree/btree_create_node parser/btree/btree_apply_prefix\
# 			parser/btree/btree_free parser/btree/__debug parser/parser\
# 			parser/rules/expr parser/rules/factor shell/shell shell/completion\
# 			interpreter/interpreter

# SRCS= $(addprefix $(SRDIR), $(SRCS_RAW:=.c))
# OBJS=$(subst .c,.o,$(SRCS))

# HEADERS_RAW= _42sh token lexer parser shell interpreter

# HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

# TESTS_DIR= tests/
# TESTS_RAW=	AllTests CuTest lexer_rules_command lexer_rules_operator\
# 			lexer_rules_unknown lexer_rules_whitespace lexer_get_token_type\
# 			lexer parser_eat parser_get_current_token parser

# TESTS= $(addprefix $(TESTS_DIR), $(TESTS_RAW:=.c)) $(filter-out src/main.c, $(SRCS))
# TESTS_OBJS=$(subst .c,.o,$(TESTS))

# NAME= 42sh

# .PHONY: all LIBFT clean fclean re

# all: $(NAME)

# # implicitly apply CFLAGS
# $(NAME): $(OBJS) $(HEADERS) Makefile
# 	$(CC) -ledit -o $(NAME) $(OBJS)

# test: $(OBJS) $(HEADERS) $(TESTS_OBJS) Makefile
# 	@echo $(TESTS_OBJS)
# 	$(CC) -o $(NAME)_test $(TESTS_OBJS)

# debug: $(NAME)
# 	$(CC) -g -fsanitize=address -o $(NAME) $(OBJS)

# clean:
# 	$(RM) $(OBJS) $(TESTS_OBJS)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all
