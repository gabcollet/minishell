#include "minishell.h"


t_token	*ms_trim_and_expand(t_token *token);
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

/*Compte le nombre de type string présente dans la struct et le retourne*/
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

/*Enregistre les token type string dans une job*/
void token_to_tab(t_token *token, t_job *job)
{
	int	i;
	int	j;
	int	counter;
	// char	*temp;
	
	if (!job->cmd)
	{
		counter = counter_string(token);
		job->cmd = ft_calloc(counter + 1, sizeof(char*));
	}
	i = 0;
	j = 0;
	while (job->cmd[i])
		i++;
	job->cmd[i] = ft_calloc((ft_strlen(token->str_tok) + 1), sizeof(char));  
	ft_strcpy(job->cmd[i], token->str_tok);
 }

/*Fonction principale qui parse l'input*/
t_job	*ms_parsing(char *line, t_job *job_first)
{
	char	*temp;
	t_parser *parser;
	t_token *first;
	t_token *first2;
	t_token	*first3;
	t_token	*first4;
	t_token *token;

	token = ms_token_newlst(NULL);
	parser = malloc(sizeof(t_parser) * 1);
	first = token;
	first2 = token;
	first3 = token;
	first4 = token;
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
	if (!valid_syntax(first4))
		return (NULL);
	token = ms_expand_tild(first);
	token = expand_dol_sign(first3);
	//printList(first);
	token = ms_trim_quotes(first);
	job_first = ms_job(job_first, first2);
	free_token_lst(first);
	return (job_first);
}

/*Vérifie si la chaine est vide*/
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

/*Trimmes les whitespace de la chaine passée en paramètre et en retourne une nouvelle*/
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