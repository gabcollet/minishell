/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:34:34 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/16 16:38:55 by gcollet          ###   ########.fr       */
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
			return (1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	ms_set_env(g_msh.env, ft_strjoin("OLDPWD=", c));
	getcwd(c, sizeof(c));
	ms_set_env(g_msh.env, ft_strjoin("PWD=", c));
	return (0);
}
