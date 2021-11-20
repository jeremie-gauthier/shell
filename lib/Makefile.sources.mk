ROOT=	lib.rs\
		token.rs

LEXER=	mod.rs\
		rules/mod.rs\
		rules/whitespace.rs

LEXER:=	$(addprefix lexer/, $(LEXER))

RUST_SOURCES=	$(addprefix src/, $(ROOT) $(LEXER))