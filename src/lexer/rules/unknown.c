#include "lexer.h"
#include "token.h"

t_token unknown(t_lexer *const restrict lexer)
{
	lexer->input_idx++;
	return (t_token){.type = Unknown, .value = NULL};
}
