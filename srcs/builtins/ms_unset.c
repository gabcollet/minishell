/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:10:20 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/05 15:49:29 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
- Annulation d'une variable ou d'une fonction qui n'a pas été précédemment
définie ne doit pas être considérée comme une erreur et n'entraîne pas un abort.
- unset test1 test2 |	Peut unset plusieurs variables en même temps 
*/

int	ms_check_unset_arg(char *arg)
{
	if (ft_isalpha(arg[0]) == 0 && arg[0] != 95)
	{
		printf("unset: '%s': not a valid identifier\n", arg);
		return (-1);
	}
	else
		return (0);
}

/* valide dans env et env_export si les ligne de unset existe et les enlèves */
char	**ms_unset_remove(char **env, char *arg)
{
	char	*line;

	line = NULL;
	line = ms_get_env(env, arg);
	if (line != NULL)
		env = ms_matrix_remove_line(env, line);
	return (env);
}

/* fonction principale du builtin unset */
int	ms_unset(char **arg)
{
	int		i;
	char	**strings;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (ms_check_unset_arg(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue;
		}
		strings = ft_split(arg[i], '=');
		g_msh.env = ms_unset_remove(g_msh.env, strings[0]);
		g_msh.env_export = ms_unset_remove(g_msh.env_export, strings[0]);
		ft_free_tab(strings);
		i++;
	}
	return (ret);
}
