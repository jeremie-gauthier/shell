HEADERS=	_42sh.h\
			token.h\
			lexer.h\
			parser.h\
			shell.h\
			interpreter.h\
			lib_io.h\
			lib_str.h

HEADERS:=	$(addprefix includes/, $(HEADERS))
