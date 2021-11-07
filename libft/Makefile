# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

STRING_DIR= string/
HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR)

RM= rm -rf

STRING_RAW= count_words

STRING = $(addprefix $(STRING_DIR), $(STRING_RAW:=.c))
STRING_OBJS=$(subst .c,.o,$(STRING))

HEADERS_RAW= strings libft

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

NAME= libft.a

ALL_OBJS= $(STRING_OBJS)

.PHONY: all clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(ALL_OBJS) $(HEADERS) Makefile
	ar rc $(NAME) $(ALL_OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
