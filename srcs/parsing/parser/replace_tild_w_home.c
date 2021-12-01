/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tild_w_home.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:53:28 by jbadia            #+#    #+#             */
/*   Updated: 2021/12/01 14:26:04 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_expand_tild(t_token *token, t_parser *parser)
{
	char	*temp;
	t_token	*head;
	t_token	*first;

	head = token;
	first = token;
	temp = NULL;
	free(parser);
	while (token && token->str_tok)
	{
		if (token->state != KEEP_IT)
		{
			temp = ft_strdup(token->str_tok);
			free(token->str_tok);
			token->str_tok = replace_tild_w_home(temp);
			free(temp);
		}
		token = token->next;
	}
	first = expand_dol_sign(first);
	return (head);
}

char	*replace_tild_w_home(char *token)
{
	char	*temp;
	char	*home;
	int		i;
	int		j;

	i = 0;
	home = ms_get_varenv(g_msh.env, "HOME");
	if (home == NULL)
		home = ft_strdup("~");
	temp = ft_calloc(tild_counter(token) * ft_strlen(home) + 1, sizeof(char));
	while (*token)
	{
		j = 0;
		if (*token == '~')
		{
			while (home[j])
				temp[i++] = home[j++];
			token++;
		}
		else
			temp[i++] = *(token++);
	}
	free(home);
	return (temp);
}

int	tild_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '~')
			counter++;
		i++;
	}
	return (counter + i);
}
