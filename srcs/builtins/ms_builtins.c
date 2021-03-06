/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:09:22 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/26 15:31:44 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0
		||ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "pwd") == 0
		||ft_strcmp(arg[0], "export") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0
		||ft_strcmp(arg[0], "exit") == 0
		||ft_strcmp(arg[0], "mafortin") == 0)
		return (0);
	else
		return (1);
}

int	ms_builtins(char **arg, int i, t_job *job)
{
	if (arg)
	{
		if (ft_strcmp(arg[0], "echo") == 0)
			g_msh.ret_exit = ms_echo(arg + 1);
		else if (ft_strcmp(arg[0], "cd") == 0)
			g_msh.ret_exit = ms_cd(arg[1]);
		else if (ft_strcmp(arg[0], "pwd") == 0)
			g_msh.ret_exit = ms_pwd();
		else if (ft_strcmp(arg[0], "export") == 0)
			g_msh.ret_exit = ms_export(arg + 1);
		else if (ft_strcmp(arg[0], "unset") == 0)
			g_msh.ret_exit = ms_unset(arg + 1);
		else if (ft_strcmp(arg[0], "env") == 0)
			g_msh.ret_exit = ms_env();
		else if (ft_strcmp(arg[0], "exit") == 0)
			ms_exit(arg + 1, job);
		else
			return (1);
	}
	if (i == 0)
		return (0);
	free_exit(job);
	exit(0);
}
