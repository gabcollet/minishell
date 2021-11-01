#include "minishell.h"

t_msh g_msh = {0};


int main(int argc, char *argv[], char **env)
{
	char *line;
	
	(void)argc;
	(void)argv;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	line = readline("TEST: ");
	ms_parsing(line);
	free(line);
}