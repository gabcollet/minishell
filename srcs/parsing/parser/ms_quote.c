/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:58:34 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/29 12:04:38 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

/*Renvoie l'index de la quote fermante ou renvoi -1*/
int	ms_find_close_quote(t_parser *parser, char quote)
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
	int		i;
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
	t_quote	*quote;

	quote = ft_calloc(1, sizeof(t_quote));
	while (token && token->str_tok)
	{
		if (token->type == STRING)
		{
			ms_init_quote_struct(quote);
			quote->temp = ft_calloc(ft_strlen(token->str_tok) + 1,
					sizeof(char *));
			quote_trimmer(quote, token);
			free(token->str_tok);
			token->str_tok = ft_strdup(quote->temp);
			free(quote->temp);
		}
		token = token->next;
	}
	free(quote);
	return (token);
}

/*Renvoi vrai si l'index est sur une quote sinon renvoi faux*/
bool	is_quote(char *tab, int i)
{
	if (tab[i] == '\'' || tab[i] == '\"')
		return (true);
	return (false);
}
