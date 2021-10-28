/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:34:34 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 14:06:18 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Effectue le builtin-cd */
int	ms_cd(char *arg)
{
	char	c[PATH_MAX];

	if (arg == NULL)
	{
		arg = ms_get_env(g_msh.env, "HOME=") + 5;
		if ((arg - 5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (-1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		printf("cd: %s: No such file or directory\n", arg);
		return (-1);
	}
	ms_set_env(g_msh.env, ft_strjoin("OLDPWD=", c));
	getcwd(c, sizeof(c));
	ms_set_env(g_msh.env, ft_strjoin("PWD=", c));
	return (0);
}
