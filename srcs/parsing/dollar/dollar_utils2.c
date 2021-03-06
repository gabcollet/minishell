/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:23:08 by jbadia            #+#    #+#             */
/*   Updated: 2021/12/08 11:04:32 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_arr_tab(t_dollar *dol)
{
	int		k;
	int		j;
	char	**space;

	k = 0;
	j = 0;
	if (is_spaces(dol->var_env))
	{
		space = ft_split(dol->var_env, ' ');
		while (space[k])
		{
			j = 0;
			while (space[k][j])
				dol->str[dol->index++] = space[k][j++];
			dol->str[dol->index++] = ' ';
			k++;
		}
		ft_free_tab(space);
	}
	else
	{
		j = 0;
		while (dol->var_env[j])
			dol->str[dol->index++] = dol->var_env[j++];
	}
}

void	*ft_free(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

int	handle_dol_var(t_dollar *dol, char *temp, int index)
{
	if (!check_dol(dol->name_var))
		index = check_name_var(dol, index);
	else
		check_var_env(dol, temp, index);
	return (index);
}

bool	is_spaces(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			spaces++;
		i++;
	}
	if (spaces != 0)
		return (true);
	return (false);
}

int	arg_len(char *tab, int i)
{
	int	k;
	int	is_dol;

	k = 0;
	is_dol = 0;
	while (tab[i] && is_dol < 1)
	{
		if (ft_strchr("$", tab[i]))
		{
			while (is_to_expend(tab, i))
			{
				k++;
				i++;
			}
			is_dol = 1;
		}
		i++;
	}
	return (k);
}
