/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:41:33 by jbadia            #+#    #+#             */
/*   Updated: 2021/12/08 10:51:44 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*va chercher la variable dans env et retourne ce qu'il y a après le = */
char	*ms_get_dolenv(char *tab, int i)
{
	char	*str;
	char	*arg;
	char	*temp;

	arg = get_arg(tab, i);
	if (arg[0] == '?')
	{
		temp = ft_itoa(g_msh.ret_exit);
		free(arg);
		return (temp);
	}
	if (!check_dol(arg))
		return (ft_free(arg));
	str = ms_get_varenv(g_msh.env, arg);
	if (!str)
		return (ft_free(arg));
	temp = ft_substr(str, 0, ft_strlen(str));
	free(arg);
	free(str);
	return (temp);
}

/*va chercher et retroune le nom de la variable
 qui suit le signe $ dans une string*/
char	*get_arg(char *tab, int i)
{
	int		k;
	char	*arg;
	int		is_dol;

	k = 0;
	is_dol = 0;
	arg = ft_calloc(arg_len(tab, i) + 1, sizeof(char *));
	while (tab[i] && is_dol < 1)
	{
		if (ft_strchr("$", tab[i]))
		{
			while (is_to_expend(tab, i))
			{
				arg[k++] = tab[i + 1];
				i++;
				if (tab[i - 1] == '$' && arg[k - 1] == '?')
					return (arg);
				is_dol = 1;
			}
			if (is_dol_zero(tab, arg, i, is_dol))
				return (arg);
		}
		i++;
	}
	return (arg);
}

t_token	*expand_dol_sign(t_token *token)
{
	char		*temp;
	t_token		*head;
	t_token		*first;
	t_dollar	*dol;

	head = token;
	first = token;
	temp = NULL;
	dol = ft_calloc(1, sizeof(t_dollar));
	ms_init_dol_struct(dol);
	while (token && token->str_tok)
	{
		temp = ft_strdup(token->str_tok);
		free(token->str_tok);
		token->str_tok = replace_dol_w_env(temp, dol);
		if (dol->type == VOID)
			token->dol = LOSE_IT;
		token = token->next;
		dol->type = STATE;
		free(temp);
	}
	first = ms_trim_quotes(first);
	free_dol_struct(dol);
	return (head);
}

bool	is_to_expend(char *tab, int i)
{
	if ((!ft_strchr(WHITESPACE, tab[i]) && !ft_strchr(WHITESPACE, tab[i + 1])
			&& !ft_strchr("$", tab[i + 1])
			&& !is_quote(tab, i + 1) && !ft_strchr("/", tab[i + 1])
			&& ft_isalnum(tab[i + 1])) || (tab[i + 1] == '?'))
		return (true);
	return (false);
}

bool	is_dol_zero(char *tab, char *arg, int i, int is_dol)
{
	if (is_dol == 0)
	{
		arg[0] = tab[i];
		return (true);
	}
	return (false);
}
