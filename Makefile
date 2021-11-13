# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR)

RM= rm -rf

SRCS_RAW=	main lexer/lexer lexer/__debug lexer/get_token_type\
			lexer/rules/whitespace lexer/rules/word\
			lexer/rules/unknown lexer/rules/operator\
			btree/btree_create_node btree/btree_apply_prefix\
			btree/__debug

SRCS= $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW= _42sh token lexer btree

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

TESTS_DIR= tests/
TESTS_RAW=	AllTests CuTest lexer_rules_word
TESTS= $(addprefix $(TESTS_DIR), $(TESTS_RAW:=.c)) $(filter-out src/main.c, $(SRCS))
TESTS_OBJS=$(subst .c,.o,$(TESTS))
# TESTS_OBJS:=
# TESTS_OBJS:= $(filter-out main.o, $(OBJS))

NAME= 42sh

.PHONY: all LIBFT clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(OBJS) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(OBJS)

test: $(OBJS) $(HEADERS) $(TESTS_OBJS) Makefile
	@echo $(TESTS_OBJS)
	$(CC) -o $(NAME)_test $(TESTS_OBJS)

clean:
	$(RM) $(OBJS) $(TESTS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
