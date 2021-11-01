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
		change_state(parser);
		if (parser->state != TEXT)
			parser->index = ms_handle_quote(parser);
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

	i = 0;
	token->str_tok = ft_calloc(parser->index + 1, sizeof(char));
	if (!token->str_tok)
		return (NULL);
	while (i < parser->index)
	{
		token->str_tok[i] = parser->str_line[i];
		i++;
	}
	ms_token_addback(&token, ms_token_newlst(NULL));
	return (token);
}