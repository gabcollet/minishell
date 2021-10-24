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
	t_token	*token;
	t_token *first;

	token = ms_token_newlst(NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	first = token;
	temp = ft_strtrim(line, WHITESPACE);
	while (!empty_str(temp))
	{
		temp = ms_init_s_parser(parser, temp);
		if (ms_get_token(parser))
		{
			token = ms_add_tok_to_lst(parser, token);
			token = token->next;
			temp = ms_get_next_tok(parser, temp);
		}
	}
	printList(first);
	free(temp);
}

char	*ms_init_s_parser(t_parser *parser, char *line)
{
	char *temp;
	char *str;

	parser->index = 0;
	parser->state = TEXT;
	temp = ft_strdup(line);
	str = temp;
	str = ft_strtrim(temp, WHITESPACE);
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
