# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

include lib/Makefile.sources.mk
include Makefile.sources.mk

RUST_SOURCES:=	$(addprefix lib/, $(RUST_SOURCES))
LIB_RS_DIR=lib/
LIB_RS_NAME=libshellmod_rs.a
LIB_RS=$(addprefix $(LIB_RS_DIR), $(LIB_RS_NAME))

HEADER_DIR= includes/

# built-in rules
CC= clang
CFLAGS= -Wall -Wextra -Werror -I$(HEADER_DIR)

RM= rm -rf

NAME= shell

.PHONY: all LIBFT clean fclean re

all: $(NAME)

# implicitly apply CFLAGS
$(NAME): $(RUST_SOURCES) $(C_OBJS_DEBUG) $(C_HEADERS) Makefile
	@make -C $(LIB_RS_DIR)
	$(CC) -ledit $(LIB_RS) -o $(NAME) $(C_OBJS_DEBUG)

release: $(LIB_RS) $(C_OBJS) $(C_HEADERS) Makefile
	@make -C $(LIB_RS_DIR) release
	$(CC) -O3 -ledit $(LIB_RS) -o $(NAME) $(C_OBJS)

test: $(C_OBJS) $(C_HEADERS) $(C_TESTS_OBJS) Makefile
	@echo $(C_TESTS_OBJS)
	$(CC) -o $(NAME)_test $(C_TESTS_OBJS)

debug: $(NAME)
	$(CC) -g -fsanitize=address -o $(NAME) $(C_OBJS_DEBUG)

clean:
	@make -C $(LIB_RS_DIR) clean
	$(RM) $(C_OBJS) $(C_TESTS_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_test

re: fclean all
