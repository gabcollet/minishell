/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:34:34 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/17 11:26:32 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(char *arg, char	*c)
{
	char	*string;

	string = ft_strjoin(arg, c);
	ms_set_env(g_msh.env, string);
	free (string);
}

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
	set_pwd("OLDPWD=", c);
	getcwd(c, sizeof(c));
	set_pwd("PWD=", c);
	return (0);
}
