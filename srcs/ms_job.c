#include "minishell.h"

void printListjob(t_job *tok)
{
	int i = 0;
	
		while(tok->cmd[i])
		{
			printf("tok[%d] = %s\n", i, tok->cmd[i]);
			i++;
		}
}

t_job	*ms_job(t_job *job, t_token *token)
{	
	t_token	*tok_first;
	t_job	*job_first;

	job = ms_job_newlst();
	tok_first = token;
	job_first = job;
	while (token)
	{
		if (token->type == PIPE)
		{
			ms_job_addback(&job, ms_job_newlst());
			job = job->next;
		}
		else if (token->type == STRING)
		{
			//je l'enregistre dans job->cmd avec un malloc en fonction de la taille des arg
			token_to_tab(token, job);
		}
		// else if (token->type == REDIR_L || token->type == REDIR_R || token->type == HERE_DOC_L || token->type == HERE_DOC_R)
		// {
		// 	//je l'enregistre dans job redir et job file
		// }
		token = token->next;
	}
	
	
	return (job_first);
}