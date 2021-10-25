#include "minishell.h"

void printList(t_token *tok)
{
	int i = 0;
	while(tok)
	{
		printf("tok[%d] = %s\n", i, tok->str_tok);
		tok = tok->next;
		i++;
	}
}

	/*
	setter ma structure avec un type en TEXT
	1 - trimmer les white spaces qui ne sont pas entre guillemets
	2- Tant que je ne rencontre pas un WS, un pipe ou une redir, je copie dans une temp que j'envoie dans ma struct token
		1 - Si je rencontre un ' ou ", je copie dans temp jusqu'à trouver la fermante
		2 - je substr str pour reprendre au prochain token
		  
	*/
	// je vérifie le type void check type()
	
void	ms_parsing(char *line)
{
	char	*temp;
	t_parser *parser;
	t_token *first;
	t_token *token;

	token = ms_token_newlst(NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	first = token;
	temp = ms_trim_space(line);
	while (!empty_str(temp))
	{
		temp = ms_init_s_parser(parser, temp);

	/*si je recontre des caractères alpha num
	  sinon si je rencontre un pipe
	  sinon si je rencontre une redir*/
		if (ms_get_token(parser))
		{
			ms_add_tok_to_lst(parser, token);
			token = token->next;
			temp = ms_get_next_tok(parser, temp);
		}
	}
	printList(first);
	free(temp);
	free(parser);
	free_token_lst(first);
}

char	*ms_init_s_parser(t_parser *parser, char *line)
{
	char *temp;
	char *str;

	parser->index = 0;
	parser->state = TEXT;
	temp = ft_strdup(line);
	str = temp;
	str = ms_trim_space(temp);
	free(temp);
	parser->str_line = str;
	free(line);
	return (str);

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