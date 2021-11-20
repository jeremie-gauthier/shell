C_ROOT=	main.c


C_LEXER=	lexer.c\
			get_token_type.c\
			rules/command.c\
			rules/unknown.c\
			rules/operator.c

C_LEXER:=	$(addprefix lexer/, $(C_LEXER))

C_LEXER_DEBUG:=	$(C_LEXER) lexer/__debug.c


C_PARSER=	parser.c\
			rules/expr.c\
			rules/factor.c\
			btree/btree_create_node.c\
			btree/btree_apply_prefix.c\
			btree/btree_free.c

C_PARSER:=	$(addprefix parser/, $(C_PARSER))

C_PARSER_DEBUG:= $(C_PARSER) parser/btree/__debug.c


_SHELL=	shell.c\
		completion.c

_SHELL:=	$(addprefix shell/, $(_SHELL))


INTERPRETER=	interpreter.c

INTERPRETER:=	$(addprefix interpreter/, $(INTERPRETER))


C_SOURCES=	$(addprefix src/, $(C_ROOT) $(C_LEXER) $(C_PARSER) $(_SHELL) $(INTERPRETER))
C_OBJS=	$(subst .c,.o,$(C_SOURCES))


C_SOURCES_DEBUG=	$(addprefix src/, $(C_ROOT) $(C_LEXER_DEBUG) $(C_PARSER_DEBUG) $(_SHELL) $(INTERPRETER))
C_OBJS_DEBUG=	$(subst .c,.o,$(C_SOURCES_DEBUG))
