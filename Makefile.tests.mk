TESTS_SOURCES=	AllTests.c\
				CuTest.c\
				lexer_rules_command.c\
				lexer_rules_operator.c\
				lexer_rules_unknown.c\
				lexer_rules_whitespace.c\
				lexer_get_token_type.c\
				lexer.c\
				parser_eat.c\
				parser_get_current_token.c\
				parser.c

TESTS_SOURCES=	$(addprefix tests/, $(TESTS_SOURCES))
TESTS_OBJS=	$(subst .c,.o,$(TESTS_SOURCES))
