/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:27:40 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/29 12:23:27 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Enregistre les credir et les pipes dans leur propre token*/
t_token	*tokenize_redir(t_parser *parser, t_token *token)
{
	char	*temp;

	temp = ft_substr(parser->str_line, 0, ft_strlen(parser->str_line));
	if (temp[0] == '|')
		token->type = PIPE;
	else if (temp[0] == '<' && temp[1] == '<')
	{
		token->type = HERE_DOC_L;
		parser->index++;
	}
	else if (temp[0] == '>' && temp[1] == '>')
	{
		token->type = APPEND;
		parser->index++;
	}
	else if (temp[0] == '<')
		token->type = REDIR_L;
	else if (temp[0] == '>')
		token->type = REDIR_R;
	free (temp);
	return (token);
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
				parser->state = D_QUOTE;
			if (parser->state == TEXT)
				parser->state = S_QUOTE;
			else if (parser->state == S_QUOTE)
			{
				parser->state = TEXT;
				token->state = KEEP_IT;
			}
		}
		change_state_2(parser, token, i);
	}
}

void	change_state_2(t_parser *parser, t_token *token, int i)
{
	if (parser->str_line[i] == '\"')
	{
		if (parser->state == S_QUOTE)
			parser->state = S_QUOTE;
		if (parser->state == TEXT)
			parser->state = D_QUOTE;
		else if (parser->state == D_QUOTE)
		{
			parser->state = TEXT;
			token->state = KEEP_IT;
		}
	}
}

/*Donne le type string au token passé en paramètre*/
t_token	*tokenize_string(t_token *token)
{
	token->type = STRING;
	return (token);
}
