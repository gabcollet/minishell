/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:09:22 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/27 15:14:39 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0)
		ms_echo(arg + 1);
	else if (ft_strcmp(arg[0], "cd") == 0)
		ms_cd(arg[1]);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		ms_pwd();
	else if (ft_strcmp(arg[0], "export") == 0)
		ms_export(arg + 1);
	else if (ft_strcmp(arg[0], "unset") == 0)
		ms_unset(arg + 1);
	else if (ft_strcmp(arg[0], "env") == 0)
		ms_env();
	else if (ft_strcmp(arg[0], "exit") == 0)
		ms_exit(arg + 1);
	else if (ft_strcmp(arg[0], "mafortin") == 0)
		printf("\e[91mThis is a very illegal function! (•̀o•́)ง\n");
}
