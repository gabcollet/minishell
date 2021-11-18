#include "minishell.h"
#include "syntax.h"

/*Renvoie l'index de la quote fermante ou renvoi -1*/
int ms_find_close_quote(t_parser *parser, char quote)
{
	int	i;

	i = parser->index + 1;
	while (parser->str_line[i])
	{
		if (parser->str_line[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

/*Renvoi l'index de la quote fermante ou print un message d'erreur*/
int	ms_handle_quote(t_parser *parser)
{
	int i;
	char	s_quote;
	char	d_quote;
	
	i = 0;
	s_quote = '\'';
	d_quote = '\"';
	if (parser->state == S_QUOTE)
	{
		i = ms_find_close_quote(parser, s_quote);
		if (i < 0)
			ms_error_quote(parser);
	}
	if (parser->state == D_QUOTE)
	{
		i = ms_find_close_quote(parser, d_quote);
		if (i < 0)
			ms_error_quote(parser);
	}
	return (i);
}

/*Trimme la sring de ses quotes et renvoie la string remalloc sans quotes*/
t_token	*ms_trim_quotes(t_token *token)
{
	char *temp;
	char quote;
	int	i;
	int	j;
	int	check;

	while (token && token->str_tok)
	{
		if (token->type == STRING)
		{
			check = 0;
			i = 0;
			j = 0;
			quote = '\0';
			temp = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char*));
			while (token && token->str_tok[i])
			{
				if (token->str_tok[i] == quote)
				{
					check++;	
					i++;
				}
				if ((token->str_tok[i] == '\'' || token->str_tok[i] == '\"') 
					&& (check == 2 || check == 0))
				{
					if (check == 2)
					{
						quote = '\0';
						check = 0;
					}
					quote = token->str_tok[i];
				}
				if (token->str_tok[i] == quote)
				{
				 	i++;
					check++;
				}
				if (token->str_tok[i] != '\0' && token->str_tok[i] != quote)
				{
					temp[j] = token->str_tok[i];
					j++;
					i++;
				}
			}
			free(token->str_tok);
			token->str_tok = ft_strdup(temp);
			free(temp);
		}
		token = token->next;
	}
	return (token);
}

/*
char *ms_remove_quote(char *str)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	j = ft_strlen(str) - 1;
	temp = ft_calloc(ft_strlen(str), sizeof(char));
	if (str[0] == '\'' || str[0] == '\"')  
		i++;
	while (i < j)
	{
		temp[i - 1] = str[i];
		i++;
	}
	return (temp);
}*/

/*Renvoi vrai si l'index est sur une quote sinon renvoi faux*/
bool is_quote(char *tab, int i)
{
	if (tab[i] == '\'' || tab[i] == '\"')
		return (true);
	return (false);
}

/*
bool is_quote_next(t_parser *parser, int i)
{
	if ((parser->str_line[i] == '\'' && parser->str_line[i + 1] == '\'') || 
		(parser->str_line[i] == '\"' && parser->str_line[i + 1] == '\"') || 
		(parser->str_line[i] == '\"' && parser->str_line[i + 1] == '\'') || 
		(parser->str_line[i] == '\'' && parser->str_line[i + 1] == '\"'))
		return (true);
	return (false);
}
*/