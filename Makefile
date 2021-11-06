# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR)

RM= rm -rf

SRCS_RAW= main

SRCS = $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW=	

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.))

NAME= 42sh

.PHONY: all clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(OBJS) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
