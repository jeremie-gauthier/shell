# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/

# READLINE_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/editline
# EXTERNAL_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/

LEXER_RS_DIR=$(SRC_DIR)lexer_rs/
LEXER_RS_LIB=$(LEXER_RS_DIR)target/debug/liblexer_rs.a
LEXER_RS_LIB_RELEASE=$(LEXER_RS_DIR)target/release/liblexer_rs.a

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -Isrc -I$(HEADER_DIR) -I$(LEXER_RS_DIR)

RM= rm -rf

SRCS_RAW=	main lexer/lexer lexer/__debug lexer/get_token_type\
			lexer/rules/whitespace lexer/rules/command\
			lexer/rules/unknown lexer/rules/operator\
			parser/btree/btree_create_node parser/btree/btree_apply_prefix\
			parser/btree/btree_free parser/btree/__debug parser/parser\
			parser/rules/expr parser/rules/factor shell/shell shell/completion\
			interpreter/interpreter

SRCS= $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW= _42sh token lexer parser shell interpreter

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

TESTS_DIR= tests/
TESTS_RAW=	AllTests CuTest lexer_rules_command lexer_rules_operator\
			lexer_rules_unknown lexer_rules_whitespace lexer_get_token_type\
			lexer parser_eat parser_get_current_token parser

TESTS= $(addprefix $(TESTS_DIR), $(TESTS_RAW:=.c)) $(filter-out src/main.c, $(SRCS))
TESTS_OBJS=$(subst .c,.o,$(TESTS))

NAME= shell

.PHONY: all LIBFT clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(OBJS) $(HEADERS) Makefile
	@make -C $(LEXER_RS_DIR)
	$(CC) -ledit $(LEXER_RS_LIB) -o $(NAME) $(OBJS)

release: $(OBJS) $(HEADERS) Makefile
	@make -C $(LEXER_RS_DIR) release
	$(CC) -O3 -ledit $(LEXER_RS_LIB_RELEASE) -o $(NAME) $(OBJS)

LEXER_LIB:
	@make -C $(LEXER_RS_DIR)

test: $(OBJS) $(HEADERS) $(TESTS_OBJS) Makefile
	@echo $(TESTS_OBJS)
	$(CC) -o $(NAME)_test $(TESTS_OBJS)

debug: $(NAME)
	$(CC) -g -fsanitize=address -o $(NAME) $(OBJS)

clean:
	@make -C $(LEXER_RS_DIR) clean
	$(RM) $(OBJS) $(TESTS_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_test

re: fclean all
