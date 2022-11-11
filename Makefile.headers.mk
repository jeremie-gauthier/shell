HEADERS=	token.h\
			lexer.h\
			parser.h\
			shell.h\
			interpreter.h\
			lib_io.h\
			lib_str.h\
			lib_mem.h\
			lib_char.h\
			ast.h\
			process.h\
			lib_ht.h\
			env.h\
			builtin.h\
			signals.h

HEADERS:=	$(addprefix includes/, $(HEADERS))
