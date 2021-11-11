#include "minishell.h"



void printListjob(t_job *tok, t_token *token);;

void printList(t_token *tok)
{
	int i = 0;
	while(tok)
	{
		printf("tok[%d] = %s\nstate = %u\n", i, tok->str_tok, tok->state);
		tok = tok->next;
		i++;
	}
}

int	counter_string(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else if (tok->type == REDIR_L || tok->type == REDIR_R 
			|| tok->type == HERE_DOC_L || tok->type == APPEND)
			tok = tok->next;
		else if (tok->type == STRING)
			i++;
		tok = tok->next;
	}
	return (i);
}

void token_to_tab(t_token *token, t_job *job)
{
	int	i;
	int	counter;
	char	*temp;
	
	if (!job->cmd)
	{
		counter = counter_string(token);
		job->cmd = calloc(counter + 1, sizeof(char*));
	}
	i = 0;
	while (job->cmd[i])
		i++;
	job->cmd[i] = malloc(sizeof(char) * (ft_strlen(token->str_tok) + 1));  
	if (is_dolsign(token->str_tok) && (token->state == TEXT))
	{
		temp = ft_strdup(token->str_tok);
		free(token->str_tok);
		token->str_tok = replace_dol_w_env(temp);
		//free(temp); //fixme ca bug si on free
	}
	ft_strcpy(job->cmd[i], token->str_tok);
 }
	
t_job	*ms_parsing(char *line, t_job *job_first)
{
	char	*temp;
	t_parser *parser;
	t_token *first;
	t_token *first2;
	t_token *token;

	token = ms_token_newlst(NULL);
	parser = malloc(sizeof(t_parser) * 1);
	first = token;
	first2 = token;
	temp = ms_trim_space(line);
	while (!empty_str(temp))
	{
		temp = ms_init_s_parser(parser, temp);
		if (ms_get_token(parser, token))
		{
			ms_add_tok_to_lst(parser, token);
			token = token->next;
			temp = ms_get_next_tok(parser, temp);
		}
	}
	free(temp);
	free(parser);
	token = ms_trim_quotes(first);
	job_first = ms_job(job_first, first2);
	//printList(first);
	 free_token_lst(first);
	return (job_first);
}

bool empty_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	if (i > 0)
		return (false);
	return (true);
}

char *ms_trim_space(char *str)
{
	char *temp;
	char *temp1;

	temp = ft_strdup(str);
	temp1 = temp;
	temp1 = ft_strtrim(temp, WHITESPACE);
	free(temp);
	return (temp1);
}