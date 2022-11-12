#include "lexer.h"
#include "token.h"

const char *unknown(t_lexer *const lexer)
{
	advance_lexer(lexer);
	return NULL;
}
