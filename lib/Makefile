CARGO_BIN ?= $(shell which cargo)

NAME=shellmod_rs

.PHONY: all clean re

all: $(NAME)

$(NAME):
	$(CARGO_BIN) build

release:
	$(CARGO_BIN) build --release

clean:
	$(CARGO_BIN) clean

re: clean $(NAME)
