# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR)

RM= rm -rf

SRCS_RAW=	main lexer/lexer lexer/__debug lexer/get_token_type\
			lexer/rules/whitespace lexer/rules/word\
			lexer/rules/number lexer/rules/unknown lexer/rules/operator

SRCS = $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW= _42sh token lexer

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

NAME= 42sh

.PHONY: all LIBFT clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(OBJS) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
