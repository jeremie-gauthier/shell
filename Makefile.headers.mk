HEADERS=	_42sh.h\
			token.h\
			lexer.h\
			parser.h\
			shell.h\
			interpreter.h\
			shellmod_rs.h

HEADERS=	$(addprefix includes/, $(HEADERS))
