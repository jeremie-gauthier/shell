#include "lib_ht.h"
#include "shell.h"

void sh_free(t_shell shell)
{
	ht_free(shell.cache);
}
