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
		i = 0;
	}
}


void printList(t_token *tok)
{
	int i = 0;
	while(tok)
	{
		printf("tok[%d] = %s\nstate = %u\n", i, tok->str_tok, tok->type);
		tok = tok->next;
		i++;
	}
}

