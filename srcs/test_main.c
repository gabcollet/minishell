#include "minishell.h"

void printListjob(t_job *tok);

t_msh g_msh = {0};

int main(int argc, char *argv[], char **env)
{
	char *line;
	t_job	*job_first;
	t_job	*job_first2;
	t_parser *parser;
	
	(void)argc;
	(void)argv;
	parser = malloc(sizeof(t_parser) * 1);
	job_first = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	line = readline("TEST: ");
	job_first = ms_parsing(line, job_first, parser);
	job_first2 = job_first;
	printListjob(job_first);
	free_job_lst(job_first2); //FIXME un pointeur qui se free pas au bon moment parfois
	free(line);
}