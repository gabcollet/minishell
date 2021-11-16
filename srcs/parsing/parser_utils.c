#include "minishell.h"

/*Enregistre les credir et les pipes dans leur propre token*/
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
			parser->index++;
			break ;
		}
		if (temp[i] == '>' && temp[i + 1] == '>')
		{
			token->type = APPEND;
			parser->index++;
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

/*state machine permettant de gérer les quotes et l'expansion du $*/
void	change_state(t_parser *parser, t_token *token)
{
	size_t	i;
	
	i = parser->index;
	{
		if (parser->str_line[i] == '\'')
		{
			if (parser->state == D_QUOTE)
			{
				parser->quote_state = KEEP_IT;
				parser->state = D_QUOTE;
			}
			if (parser->state == TEXT)
			{
				parser->state = S_QUOTE;
			}
			else if (parser->state == S_QUOTE)
			{
				parser->state = TEXT;
				token->state = NO_DOL;
			}
		}
		if (parser->str_line[i] == '\"')
		{
			if (parser->state == S_QUOTE)
			{
				parser->quote_state = KEEP_IT;
				parser->state = S_QUOTE;
			}
			if (parser->state == TEXT)
			{
				parser->state = D_QUOTE;
			}
			else if (parser->state == D_QUOTE)
			{
				parser->state = TEXT;
				token->state = TEXT;
			}
		}
	}
}

/*Donne le type string au token passé en paramètre*/
bool tokenize_string(t_token *token)
{
	token->type = STRING;
	return (true);
}
