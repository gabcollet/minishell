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

void	ms_parsing(char *line, t_parser *parser, t_token *token)
{
	char	*temp;

	ms_init_s_parser(parser);
	parser->str_line = ft_strdup(line);
	/*
	setter ma structure avec un type en TEXT
	1 - trimmer les white spaces qui ne sont pas entre guillemets
	2- Tant que je ne rencontre pas un WS, un pipe ou une redir, je copie dans une temp que j'envoie dans ma struct token
		1 - Si je rencontre un ' ou ", je copie dans temp jusqu'à trouver la fermante
		2 - je substr str pour reprendre au prochain token
		  
	*/
	// je vérifie le type void check type()
	token = ms_token_new(NULL);
	while (empty_str(parser->str_line))
	{
		parser->str_line = ft_strtrim(parser->str_line, WHITESPACE);
		parser->index = 0;
		temp = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		while ((!ft_strchr(REDIRECTION, parser->str_line[parser->index])) 
			&& (!ft_strchr(WHITESPACE, parser->str_line[parser->index])))
		{
			//si mon check type n'est pas sur TEXT, c'est que je suis tombée sur une " '
				// je vérifie que j'ai bien une guillemet fermante si non, message d'erreur
			temp[parser->index] = parser->str_line[parser->index];
			parser->index++;
		}
		ms_add_tok_to_list(token, temp);
		parser->str_line = ft_substr(parser->str_line, parser->index, ft_strlen(parser->str_line) - parser->index);
		printList(token);
	}
	

}

void	ms_init_s_token(t_token *token)
{
	token->next = NULL;
	token->str_tok = NULL;
	token->type = STRING;
}

void	ms_init_s_parser(t_parser *parser)
{
	parser->index = 0;
	parser->state = TEXT;
}

bool empty_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	if (i > 0)
		return (true);
	return (false);
}
