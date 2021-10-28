#include "minishell.h"

bool	tokenize_redir(t_parser *parser, t_token *token)
{
	char *temp;
	size_t	i;

	i = 0;
	temp = ft_substr(parser->str_line, 0, ft_strlen(parser->str_line));
	while(temp[i])
	{
		if (temp[i] == '|')
		{
			token->type = PIPE;
			break ;
		}
		if (temp[i] == '<' && temp[i + 1] == '<')
		{
			token->type = HERE_DOC_L;
			parser->index += 2;
			break ;
		}
		if (temp[i] == '>' && temp[i + 1] == '>')
		{
			token->type = HERE_DOC_R;
			parser->index += 2;
			break ;
		}
		else if (temp[i] == '<')
		{
			token->type = REDIR_L;
			break ;
		}
		else if (temp[i] == '>')
		{
			token->type = REDIR_R;
			break ;
		}
		i++;
	}
	free(temp);
	return(true);
}

void	change_state(t_parser *parser)
{
	size_t	i;
	

	i = parser->index;
	{
		if (parser->str_line[i] == '\'')
		{
			if (parser->state == D_QUOTE)
				parser->state = D_QUOTE;
			if (parser->state == TEXT)
				parser->state = S_QUOTE;
			else if (parser->state == S_QUOTE)
				parser->state = TEXT;
		}
		if (parser->str_line[i] == '\"')
		{
			if (parser->state == S_QUOTE)
				parser->state = S_QUOTE;
			if (parser->state == TEXT)
				parser->state = D_QUOTE;
			else if (parser->state == D_QUOTE)
				parser->state = TEXT;
		}
	}
}

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

int	ms_handle_quote(t_parser *parser)
{
	int i;
	
	i = 0;
	if (parser->state == S_QUOTE)
	{
		i = ms_find_close_quote(parser, '\'');
		if (i < 0)
			ms_error_quote(parser);
	}
	if (parser->state == D_QUOTE)
	{
		i = ms_find_close_quote(parser, '\"');
		if (i < 0)
			ms_error_quote(parser);
	}
	return (i);
}

bool tokenize_string(t_token *token)
{
	token->type = STRING;
	return (true);
}