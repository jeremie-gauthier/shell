#include "env.h"
#include "lib_arr.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"
#include <stdbool.h>

#include <stdio.h>

// TODO: add recursive replacement if nested params exps
bool subst_param_exps(t_shell *const shell, t_word_token *word)
{
	if (!word->param_expansions)
		return true;

	// substitute all individual expansion token
	for (size_t i = 0; i < word->param_expansions->size; i++)
	{
		t_expansion_token *expansion = word->param_expansions->items[i];
		char *substitution = env_get(shell->env, expansion->parameter);
		if (!substitution)
			return false;
		expansion->substitution = ft_strdup(substitution);
	}

	// TODO: optimize this part
	// build the word substitution
	char **word_substs = NULL;
	size_t current_pos = 0;
	size_t arr_size = 0;
	for (size_t i = 0; i < word->param_expansions->size; i++)
	{
		t_expansion_token *expansion = word->param_expansions->items[i];

		// copy str before exp subst
		const size_t slice_non_subst_str = expansion->loc.start - current_pos;
		if (slice_non_subst_str > 0)
		{
			const char *const non_subst_str = ft_strndup(&word->text[current_pos], slice_non_subst_str);
			word_substs = ft_arr_append(word_substs, non_subst_str);
			arr_size++;
		}

		// copy exp subst
		word_substs = ft_arr_append(word_substs, expansion->substitution);
		arr_size++;
		current_pos = expansion->loc.end + 1;
	}

	// copy str after last exp subst
	word_substs = ft_arr_append(word_substs, &word->text[current_pos]);
	arr_size++;

	word->substitution = ft_arr_join(word_substs);
	ft_arr_free(word_substs, arr_size);

	return true;
}

bool subst_cmd_words(t_shell *const shell, t_command_token *command)
{
	if (!subst_param_exps(shell, command->name))
		return false;

	if (command->suffix)
		for (size_t i = 0; i < command->suffix->size; i++)
		{
			t_word_token *word = command->suffix->items[i];
			if (!subst_param_exps(shell, word))
				return false;
		}

	return true;
}
