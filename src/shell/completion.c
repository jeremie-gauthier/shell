#include <stddef.h>
#include <string.h>
#include <editline/readline.h>

static char *command_generator(const char *const text, const int state)
{
	static int list_index, len;

	HIST_ENTRY *history;

	/* If this is a new word to complete, initialize now.  This includes
	   saving the length of TEXT for efficiency, and initializing the index
	   variable to 0. */
	if (!state)
	{
		list_index = 0;
		len = strlen(text);
	}

	/* Return the next name which partially matches from the command list. */
	while ((history = history_get(list_index + 1)))
	{
		list_index++;

		if (strncmp(history->line, text, len) == 0)
			return strdup(history->line);
	}

	/* If no names matched, then return NULL. */
	return NULL;
}

char **command_completion(const char *const text, const int start)
{
	char **matches = NULL;

	/* If this word is at the start of the line, then it is a command
	   to complete.  Otherwise it is the name of a file in the current
	   directory. */
	if (start == 0)
		matches = completion_matches(text, command_generator);

	return matches;
}
