#include "lexer.h"
#include "token.h"

t_token unknown(t_lexer *const restrict lexer)
{
	advance_lexer(lexer);
	return (t_token){.type = Unknown, .value = NULL};
}
