/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:10:20 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/25 15:16:15 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
- Annulation d'une variable ou d'une fonction qui n'a pas été précédemment
définie ne doit pas être considérée comme une erreur et n'entraîne pas un abort.
- unset test1 test2 |	Peut unset plusieurs variables en même temps 
*/

char	**ms_unset_remove(char **env, char *arg)
{
	char	*line;
	line = NULL;
	line = ms_get_env(env, arg);
	if (line != NULL)
		env = ms_matrix_remove_line(env, line);
	return (env);
}

int	ms_unset(char **arg)
{
	int		i;
	char	**strings;
	
	i = 0;
	while (arg[i])
	{
		strings = ft_split(arg[i], '=');
		g_msh.env = ms_unset_remove(g_msh.env, strings[0]);
		g_msh.env_export = ms_unset_remove(g_msh.env_export, strings[0]);
		ft_free_tab(strings);
		i++;
	}
	return (0);
}
