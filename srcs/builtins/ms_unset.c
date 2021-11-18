/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:10:20 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/17 11:27:52 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("unset: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			printf("unset: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

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
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (ms_check_unset_arg(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue ;
		}
		strings = ft_split(arg[i], '=');
		g_msh.env = ms_unset_remove(g_msh.env, strings[0]);
		g_msh.env_export = ms_unset_remove(g_msh.env_export, strings[0]);
		ft_free_tab(strings);
		i++;
	}
	return (ret);
}
