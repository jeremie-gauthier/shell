CARGO_BIN ?= $(shell which cargo)

NAME=shellmod_rs

SRCS=src/lexer/rules/whitespace.rs

.PHONY: all clean re

all: $(NAME)

$(NAME): $(SRCS)
	$(CARGO_BIN) fmt
	$(CARGO_BIN) build
	cp ./target/debug/lib$(NAME).a .

release:
	$(CARGO_BIN) fmt
	$(CARGO_BIN) build --release
	cp ./target/release/lib$(NAME).a .

clean:
	$(CARGO_BIN) clean

re: clean $(NAME)
