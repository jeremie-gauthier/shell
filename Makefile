# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

SRC_DIR= src/
HEADER_DIR= includes/
LIBFT_DIR = libft/
LIBFT_HEADER_DIR= $(addprefix $(LIBFT_DIR), includes/)

LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I $(HEADER_DIR) -I $(LIBFT_HEADER_DIR)
LFLAGS= -L $(LIBFT_DIR) -lft

RM= rm -rf

SRCS_RAW= main

SRCS = $(addprefix $(SRC_DIR), $(SRCS_RAW:=.c))
OBJS=$(subst .c,.o,$(SRCS))

HEADERS_RAW= _42sh

HEADERS=$(addprefix $(HEADER_DIR), $(HEADERS_RAW:=.h))

NAME= 42sh

.PHONY: all LIBFT clean fclean re

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) -j4

# implicitly apply CFLAGS
$(NAME): $(LIBFT) $(OBJS) $(HEADERS) Makefile
	$(CC) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
