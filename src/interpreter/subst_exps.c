#include "env.h"
#include "lib_arr.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>

static size_t count_regular_chars(const t_word_token *const word)
{
	size_t count = 0;
	size_t current_idx = 0;

	for (size_t i = 0; i < word->expansions->size; i++)
	{
		const t_expansion_token *exp_param = word->expansions->items[i];
		count += (exp_param->loc.start - current_idx);
		current_idx = exp_param->loc.end + 1;
	}
	if (word->text[current_idx])
		current_idx += (ft_strlen(word->text) - current_idx);
	return count;
}

const char *get_param_exp_subst(const t_shell *const shell, const t_expansion_token *const expansion)
{
	// ? This is the only kind of substitution supported as of now
	if (expansion->param_exp_type != SimpleSubstitution)
		return NULL;

	// ? just env as of now, but in future, logic will be added to expand from variable or smthg else
	const char *substitution = (const char *)env_get(shell->env, expansion->parameter);
	if (!substitution)
		return NULL;

	return ft_strdup(substitution);
}

const char *get_tilde_exp_subst(const t_shell *const shell, const t_expansion_token *const expansion)
{
	switch (expansion->tilde_exp_type)
	{
	case Literal:
		return expansion->parameter;
	case Home:
		return env_get(shell->env, "HOME");
	case Pwd:
		return env_get(shell->env, "PWD");
	case Oldpwd:
		return env_get(shell->env, "OLDPWD");
	default:
		return NULL;
	}
}

// aggregation of all the expansion subst (as a word can have multiple subst)
char *get_word_subst(const t_word_token *const word)
{
	size_t word_subst_len = count_regular_chars(word);
	for (size_t i = 0; i < word->expansions->size; i++)
	{
		t_expansion_token *expansion = word->expansions->items[i];
		word_subst_len += ft_strlen(expansion->substitution);
	}

	char *word_subst = ft_strnew(word_subst_len);
	if (!word_subst)
		return NULL;

	size_t src_str_idx = 0;
	size_t dst_str_idx = 0;
	for (size_t i = 0; i < word->expansions->size; i++)
	{
		t_expansion_token *expansion = word->expansions->items[i];

		size_t copy_length = expansion->loc.start - src_str_idx;
		ft_strncpy(&word_subst[dst_str_idx], word->text, copy_length);
		dst_str_idx += copy_length;

		ft_strcpy(&word_subst[dst_str_idx], expansion->substitution);
		dst_str_idx += ft_strlen(expansion->substitution);
		src_str_idx += expansion->loc.end + 1;
	}
	ft_strcpy(&word_subst[dst_str_idx], &word->text[src_str_idx]);

	return word_subst;
}

// TODO: add recursive replacement if nested params exps
bool subst_exps(t_shell *const shell, t_word_token *word)
{
	if (!word->expansions)
		return true;

	const char *(*exp_subst_fn[2])(const t_shell *const shell, const t_expansion_token *const expansion);
	exp_subst_fn[Parameter] = get_param_exp_subst;
	exp_subst_fn[Tilde] = get_tilde_exp_subst;

	// substitute all individual expansion token
	for (size_t i = 0; i < word->expansions->size; i++)
	{
		t_expansion_token *expansion = word->expansions->items[i];
		expansion->substitution = (char *)exp_subst_fn[expansion->type](shell, expansion);
		if (!expansion->substitution)
			return false;
	}

	word->substitution = get_word_subst(word);
	if (!word->substitution)
		return false;

	return true;
}

bool subst_cmd_words(t_shell *const shell, t_command_token *command)
{
	if (!subst_exps(shell, command->name))
		return false;

	if (command->suffix)
		for (size_t i = 0; i < command->suffix->size; i++)
		{
			t_word_token *word = command->suffix->items[i];
			if (!subst_exps(shell, word))
				return false;
		}

	return true;
}
