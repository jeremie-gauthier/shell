TESTS_SOURCES=	AllTests.c\
				CuTest.c\
				lib_char.c

TESTS_SOURCES:=	$(addprefix tests/, $(TESTS_SOURCES))
TESTS_OBJS=	$(subst .c,.o,$(TESTS_SOURCES))
