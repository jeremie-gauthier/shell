#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

t_token unknown(t_lexer *const lexer)
{
	lexer->input_idx++;
	return (t_token) { .type = Unknown, .value = NULL };
}
