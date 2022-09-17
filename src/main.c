#include "lib_ht.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_ht *ht = ht_create();
	ht_set(ht, "1", "First address");
	ht_set(ht, "2", "Second address");
	ht_set(ht, "Hel", "Third address");
	ht_set(ht, "Cau", "Fourth address");
	print_search(ht, "1");
	print_search(ht, "2");
	print_search(ht, "3");
	print_search(ht, "Hel");
	print_search(ht, "Cau"); // Collision!
	print_table(ht);
	ht_delete(ht, "1");
	ht_delete(ht, "Cau");
	print_table(ht);
	ht_free(ht);
	(void)env;

	// t_shell shell;

	// shell = create_shell(env);
	// run_shell(shell);
	return EXIT_SUCCESS;
}
