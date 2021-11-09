#include "minishell.h"

void printListjob(t_job *tok)
{
	
	int j = 0;
	int k;
	while (tok)
	{
		int i = 0;
		printf("\n------- JOB %d -------\n", j);
		j++;
		while(tok->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, tok->cmd[i]);
			i++;
		}
		k = 0;
		// while (tok->redir->file && tok->redir->file[k])
		// {
		// 	printf("redir[%d] = %s\n", k, tok->redir->file[k]);
		// 	printf("       |__ type = %u\n", tok->redir->type);
		// 	k++;
		// }
		tok = tok->next;
	}
}

bool is_redirection(t_token *token)
{
	if (token->type == REDIR_L || token->type == REDIR_R
		|| token->type == HERE_DOC_L || token->type == HERE_DOC_R)
		return (true);
	return (false);
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
			token_to_tab(token, job);
		else if (is_redirection(token))
		{
			redirection_to_tab(token, job);
			token = token->next;
		}
		token = token->next;
	}
	return (job_first);
}

void	redirection_to_tab(t_token *token, t_job *job)
{
	int	counter;
	int	i;

	if (!job->redir->file)
	{
		counter = redir_counter(token);
		/* printf("\nNOMBRE DE REDIR = %d\n\n", counter); */
		job->redir->file = (char **)ft_calloc(counter + 1, sizeof (char *));
	}
	i = 0;
	while (job->redir->file[i])
		i++;
	job->redir->file[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char));
	ft_strlcpy(job->redir->file[i], token->str_tok, ft_strlen(token->str_tok) + 1);
	job->redir->type = token->type;
	token = token->next;
	i++;
	job->redir->file[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char));
	ft_strlcpy(job->redir->file[i], token->str_tok, ft_strlen(token->str_tok) + 1);
}

int	redir_counter(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else if (is_redirection(tok))
			i++;
		else if (tok->type == STRING)
			tok = tok->next;
		tok = tok->next;
	}
	return (i);
}