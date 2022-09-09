ROOT=	main.c


LEXER=	lexer.c\
		get_token_type.c\
		rules/command.c\
		rules/unknown.c\
		rules/whitespace.c\
		rules/operator.c

LEXER:=	$(addprefix lexer/, $(LEXER))

LEXER_DEBUG:=	$(LEXER) lexer/__debug.c


PARSER=	parser.c\
		rules/expr.c\
		rules/factor.c\
		btree/btree_create_node.c\
		btree/btree_apply_prefix.c\
		btree/btree_free.c

PARSER:=	$(addprefix parser/, $(PARSER))

PARSER_DEBUG:= $(PARSER) parser/btree/__debug.c


_SHELL=	shell.c

_SHELL:=	$(addprefix shell/, $(_SHELL))


INTERPRETER=	interpreter.c

INTERPRETER:=	$(addprefix interpreter/, $(INTERPRETER))


SOURCES=	$(addprefix src/, $(ROOT) $(LEXER) $(PARSER) $(_SHELL) $(INTERPRETER))
OBJS=	$(subst .c,.o,$(SOURCES))


SOURCES_DEBUG=	$(addprefix src/, $(ROOT) $(LEXER_DEBUG) $(PARSER_DEBUG) $(_SHELL) $(INTERPRETER))
OBJS_DEBUG=	$(subst .c,.o,$(SOURCES_DEBUG))
