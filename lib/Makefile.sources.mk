ROOT=	lib.rs

LEXER=	mod.rs\
		lexer.rs\
		rules/mod.rs\
		rules/whitespace.rs

LEXER:=	$(addprefix lexer/, $(LEXER))

PARSER=	mod.rs

PARSER:=$(addprefix parser/, $(PARSER))

RUST_SOURCES=	$(addprefix src/, $(ROOT) $(LEXER) $(PARSER))
