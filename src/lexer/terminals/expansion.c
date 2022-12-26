#include "lexer.h"
#include "token.h"

t_expansion_token *parse_expansion(t_lexer *const lexer)
{
	switch (lexer->current_char)
	{
	case EXP_PARAM_CHAR:
		return parse_param_expansion(lexer);
	case TILDE_PARAM_CHAR:
		return parse_tilde_expansion(lexer);
	default:
		return NULL;
	}
}