#ifndef SHELL_H
#define SHELL_H

enum e_shell_status
{
	STOPPED = 0,
	RUNNING
};

typedef struct shell
{
	enum e_shell_status status;
	char **env;
} t_shell;

t_shell create_shell(void);
int run_shell(t_shell shell);

#endif
