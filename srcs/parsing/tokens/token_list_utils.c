/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:03:21 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/18 17:03:34 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_token_addback(t_token **token, t_token *new_tok)
{
	t_token	*last_tok;

	if (*token == NULL)
		*token = new_tok;
	else
	{
		last_tok = ms_token_last(*token);
		last_tok->next = new_tok;
		new_tok->previous = last_tok;
	}
}

t_token	*ms_token_last(t_token	*token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

t_token	*ms_token_newlst(void *token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->str_tok = token;
	new->type = VOID;
	new->state = TEXT;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

t_token	*ms_head_list(t_token *token)
{
	while (token)
	{
		if (!token->previous)
			return (token);
		token = token->previous;
	}
	return (token);
}
