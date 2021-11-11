#include "minishell.h"

void printListjob(t_job *tok);

t_msh g_msh = {0};

int main(int argc, char *argv[], char **env)
{
	char *line;
	t_job	*job_first;
	t_job	*job_first2;
	
	(void)argc;
	(void)argv;
	job_first = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	line = readline("TEST: ");
	job_first = ms_parsing(line, job_first);
	job_first2 = job_first;
	// printListjob(job_first);
	//TODO free les leaks de la struct job
	free(line);
}