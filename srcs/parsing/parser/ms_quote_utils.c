/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:43:54 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/19 10:35:34 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

void	ms_init_quote_struct(t_quote *quote)
{
	quote->quote = '\0';
	quote->i = 0;
	quote->j = 0;
	quote->check = 0;
}

void	quote_updater(t_quote *quote)
{
	quote->check++;
	quote->i++;
}

void	quote_trimmer(t_quote *quote, t_token *token)
{
	while (token && token->str_tok[quote->i])
	{
		if (token->str_tok[quote->i] == quote->quote)
			quote_updater(quote);
		if ((token->str_tok[quote->i] == '\''
				|| token->str_tok[quote->i] == '\"')
			&& (quote->check == 2 || quote->check == 0))
		{
			if (quote->check == 2)
			{
				quote->quote = '\0';
				quote->check = 0;
			}
			quote->quote = token->str_tok[quote->i];
		}
		if (token->str_tok[quote->i] == quote->quote)
			quote_updater(quote);
		if (token->str_tok[quote->i] != '\0'
			&& token->str_tok[quote->i] != quote->quote)
			quote->temp[quote->j++] = token->str_tok[quote->i++];
	}
}
