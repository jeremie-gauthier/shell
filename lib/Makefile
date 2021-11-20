include Makefile.sources.mk

CARGO_BIN ?= $(shell which cargo)

NAME=shellmod_rs

.PHONY: all clean re

all: $(NAME)

$(NAME): $(RUST_SOURCES)
	$(CARGO_BIN) fmt
	$(CARGO_BIN) build
	cp ./target/debug/lib$(NAME).a .

release: $(RUST_SOURCES)
	$(CARGO_BIN) fmt
	$(CARGO_BIN) build --release
	cp ./target/release/lib$(NAME).a .

clean:
	$(CARGO_BIN) clean

re: clean $(NAME)
