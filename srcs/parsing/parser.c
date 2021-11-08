#include "minishell.h"

void printListjob(t_job *tok, t_token *token);;

void printList(t_token *tok)
{
	int i = 0;
	while(tok)
	{
		printf("tok[%d] = %s\ntype = %u\n", i, tok->str_tok, tok->type);
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
			|| tok->type == HERE_DOC_L || tok->type == HERE_DOC_R)
			tok = tok->next->next;
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
	
	if (!job->cmd)
	{
		counter = counter_string(token);
		job->cmd = (char**)ft_calloc(counter + 1, sizeof(char*));
	}
	i = 0;
	while (job->cmd[i])
		i++;
	job->cmd[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char*));
	if (is_dolsign(token->str_tok) && (token->state == TEXT))
		replace_dol_w_env(token->str_tok, token);
		//replace_dol_w_env(&job->cmd[i], job, i);
	ft_strlcpy(job->cmd[i], token->str_tok, ft_strlen(token->str_tok) + 1);
}
	
t_job	*ms_parsing(char *line, t_job *job_first)
{
	char	*temp;
	t_parser *parser;
	t_token *first;
	t_token *first2;
	t_token *token;

	token = ms_token_newlst(NULL);
	parser = ft_calloc(1, sizeof(t_parser));
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
	//token = ms_check_quote(first);
	free(temp);
	free(parser);
	//printList(first);
	token = ms_trim_quotes(first);
	job_first = ms_job(job_first, first2);
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