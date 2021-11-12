/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:37:01 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/12 11:01:17 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *arg, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	exit (127);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	/* write and append (>>) */
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	/* write and trunc (>) */
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	/* read only (<) */
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		printf("minishell: no such file or directory: %s\n", argv);
		exit(1);
	}
	return (file);
}

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(g_msh.env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(g_msh.env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}
