ROOT=	lib.rs

LEXER=	mod.rs\
		terminals/mod.rs\
		terminals/word.rs\
		terminals/operator.rs

LEXER:=	$(addprefix lexer/, $(LEXER))

PARSER=	mod.rs\
		error.rs\
		parser.rs\
		rules/mod.rs\
		rules/arg.rs\
		rules/cmd.rs\
		rules/expr.rs

PARSER:=$(addprefix parser/, $(PARSER))

RUST_SOURCES=	$(addprefix src/, $(ROOT) $(LEXER) $(PARSER))
