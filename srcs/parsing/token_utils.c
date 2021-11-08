#include "minishell.h"


bool ms_get_token(t_parser *parser, t_token *token)
{
	if (ft_strchr(REDIRECTION, parser->str_line[parser->index]))
	{
		parser->index++;
		return (tokenize_redir(parser, token));
	}
	while ((!ft_strchr(REDIRECTION, parser->str_line[parser->index])) 
	&& (!ft_strchr(WHITESPACE, parser->str_line[parser->index])))
	{
		change_state(parser, token);
		if (parser->state != TEXT)
		{
			parser->index = ms_handle_quote(parser);
			change_state(parser, token);
		}
		parser->index++;
	}
		return(tokenize_string(token));
}

char *ms_get_next_tok(t_parser *parser, char *temp)
{
	char *str;

	str = temp;
	str = ft_substr(parser->str_line, parser->index, ft_strlen(parser->str_line) - parser->index);
	free(temp);
	return (str);
}

t_token	*ms_add_tok_to_lst(t_parser *parser, t_token *token)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	token->str_tok = ft_calloc(parser->index + 1, sizeof(char));
	if (!token->str_tok)
		return (NULL);
	while (i < parser->index)
	{
		/*if (parser->quote_state == KEEP_IT)
		{
			ms_remove_quote(token->str_tok);
			return (token);
		}
		if (is_quote_next(parser, i) && (parser->quote_state != KEEP_IT))
			i++;
		if (is_quote(parser, i) && (parser->quote_state != KEEP_IT))
			i++;*/
		token->str_tok[i] = parser->str_line[i];
		i++;
	}
	token->str_tok[i] = '\0';
	ms_token_addback(&token, ms_token_newlst(NULL));
	return (token);
}
