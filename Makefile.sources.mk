ROOT=	main.c

LEXER=	lexer_create.c\
		lexer_utils.c\
		terminals/word.c\
		terminals/unknown.c\
		terminals/whitespace.c

LEXER:=	$(addprefix lexer/, $(LEXER))

LEXER_DEBUG:=	$(LEXER) lexer/__debug.c


ENV=	env_get.c\
		env_load.c

ENV:=	$(addprefix env/, $(ENV))


PARSER=	parser_create.c\
		parser_eat.c\
		parser_run.c\
		rules/cmd.c\
		rules/expr.c

PARSER:=	$(addprefix parser/, $(PARSER))

PARSER_DEBUG:= $(PARSER)


AST=ast_create_node.c\
	ast_apply_prefix.c\
	ast_free.c
AST:=	$(addprefix ast/, $(AST))

AST_DEBUG:= $(AST) ast/__debug.c


_SHELL=	sh_create.c\
		sh_run.c\
		sh_free.c

_SHELL:=	$(addprefix shell/, $(_SHELL))


INTERPRETER=interpreter.c\
			visitors/word_visitor.c

INTERPRETER:=	$(addprefix interpreter/, $(INTERPRETER))


PROCESS=process.c\
			command.c

PROCESS:=	$(addprefix process/, $(PROCESS))


SOURCES=	$(addprefix src/, $(ROOT) $(LEXER) $(PARSER) $(_SHELL) $(INTERPRETER) $(AST) $(PROCESS) $(ENV))
OBJS=	$(subst .c,.o,$(SOURCES))


SOURCES_DEBUG=	$(addprefix src/, $(ROOT) $(LEXER_DEBUG) $(PARSER_DEBUG) $(_SHELL) $(INTERPRETER) $(AST_DEBUG) $(PROCESS) $(ENV))
OBJS_DEBUG=	$(subst .c,.o,$(SOURCES_DEBUG))