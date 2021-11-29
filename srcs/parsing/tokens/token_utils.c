/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:36:26 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/29 14:42:53 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*tokenize la string et renvoie vers tokenize_redir ou tokeniz_string*/
t_token	*ms_get_token(t_parser *parser, t_token *token)
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
			if (parser->index < 0)
			{
				free_token_lst(ms_head_list(token));
				return (NULL);
			}
			change_state(parser, token);
		}
		parser->index++;
	}
	return (tokenize_string(token));
}

/*renvoie la string de l'input en retirant le morceau de string
qui vient d'etre copié dans le token précédent*/
char	*ms_get_next_tok(t_parser *parser, char *temp)
{
	char	*str;

	if (temp)
	{
		str = temp;
		str = ft_substr(parser->str_line, parser->index,
				ft_strlen(parser->str_line) - parser->index);
		free(temp);
		return (str);
	}
	return (NULL);
}

/*Copie l'input dans la struct token puis ajoute un token null à la suite*/
t_token	*ms_add_tok_to_lst(t_parser *parser, t_token *token)
{
	int	i;

	i = 0;
	token->str_tok = ft_calloc(parser->index + 1, sizeof(char));
	if (!token->str_tok)
		return (NULL);
	while (i < parser->index)
	{
		token->str_tok[i] = parser->str_line[i];
		i++;
	}
	token->str_tok[i] = '\0';
	ms_token_addback(&token, ms_token_newlst(NULL));
	return (token);
}
