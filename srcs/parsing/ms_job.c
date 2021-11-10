#include "minishell.h"

void printListjob(t_job *tok)
{
	
	int j = 0;
	int k;
	k = 0;
	int i = 0;
	while (tok)
	{
		printf("\n------- JOB %d -------\n", j);
		j++;
		while(tok->cmd && tok->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, tok->cmd[i]);
			i++;
		}
	
		 while (tok->file /*&& tok->file[k]*/)
		{
			printf("redir[%d] = %s\n", k, tok->file[k]);
			if (tok->file[k] == NULL)
				return ;
			k++;
		}
		tok = tok->next;
	}
}

bool is_redirection(t_token *token)
{
	if (token->type == REDIR_L || token->type == REDIR_R
		|| token->type == HERE_DOC_L || token->type == APPEND)
		return (true);
	return (false);
}

t_job	*ms_job(t_job *job, t_token *token)
{	
	t_token	*tok_first;
	t_job	*job_first;
	t_job	*job_dol;

	job = ms_job_newlst();
	tok_first = token;
	job_first = job;
	job_dol = job;
	while (token && token->str_tok)
	{
		if (token->type == PIPE)
		{
			ms_job_addback(&job, ms_job_newlst());
			job = job->next;
		}
		else if (token->type == STRING)	
			token_to_tab(token, job);
		else if (is_redirection(token))
		{
			job = redirection_to_tab(token, job);
			token = token->next;
		}
		token = token->next;
	}
	printf("redir[] dans ms_job= %s\n", job->file[0]);
	return (job_first);
}

t_job	*redirection_to_tab(t_token *token, t_job *job)
{
	int	counter;
	int	i;
	if (!job->file)
	{
		counter = redir_counter(token);
		printf("\nNOMBRE DE REDIR = %d\n\n", counter);
		job->file = (char**)ft_calloc((counter *2) + 1, sizeof(char*));
	}
	i = 0;
	while (job->file[i])
		i++;
	job->file[i] = ft_calloc(ft_strlen(token->str_tok) + 2, sizeof(char));
	ft_strcpy(job->file[i], token->str_tok);
	printf("%s\n", job->file[i]);
	i++;
	if (!token->next)
		return (job);
	token = token->next;
	job->file[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char));
	ft_strcpy(job->file[i], token->str_tok);
	printf("redir[0] dans redir to tab= %s\n", job->file[0]);
	return (job);
}

int	redir_counter(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		if (tok->type == STRING)
			tok = tok->next;
		if (is_redirection(tok))
			i++;
		tok = tok->next;
	}
	return (i);
}