# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR)

RM= rm -rf

SRCS_RAW=	main lexer/lexer lexer/__debug lexer/get_token_type\
			lexer/rules/whitespace lexer/rules/command\
			lexer/rules/unknown lexer/rules/operator\
			parser/btree/btree_create_node parser/btree/btree_apply_prefix\
			parser/btree/btree_free parser/btree/__debug parser/parser\
			parser/rules/expr parser/rules/factor

SRCS= $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW= _42sh token lexer parser

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

TESTS_DIR= tests/
TESTS_RAW=	AllTests CuTest lexer_rules_command
TESTS= $(addprefix $(TESTS_DIR), $(TESTS_RAW:=.c)) $(filter-out src/main.c, $(SRCS))
TESTS_OBJS=$(subst .c,.o,$(TESTS))

NAME= 42sh

.PHONY: all LIBFT clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(OBJS) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(OBJS)

test: $(OBJS) $(HEADERS) $(TESTS_OBJS) Makefile
	@echo $(TESTS_OBJS)
	$(CC) -o $(NAME)_test $(TESTS_OBJS)

debug: $(NAME)
	$(CC) -g -fsanitize=address -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(TESTS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
