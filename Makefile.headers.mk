HEADERS=	token.h\
			lexer.h\
			parser.h\
			shell.h\
			interpreter.h\
			lib_io.h\
			lib_str.h\
			lib_mem.h\
			lib_char.h\
			ast.h

HEADERS:=	$(addprefix includes/, $(HEADERS))
