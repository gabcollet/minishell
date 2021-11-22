/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:23:08 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/22 10:23:09 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_arr_tab(t_dollar *dol)
{
	int	k;
	int	j;
	char **space;

	k = 0;
	j = 0;
	space = ft_split(dol->var_env, ' ');
	while (space[k])
	{
		j = 0;
		while (space[k][j])
			dol->str[dol->index++] = space[k][j++];
		dol->str[dol->index++] = ' ';
		k++;
	}
	return (space);
}