/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:37:01 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/24 11:09:29 by jbadia           ###   ########.fr       */
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
	else if (i == 2)
	{
		printf("minishell: %s: is a directory\n", arg);
		exit(126);
	}
	exit (127);
}

int	open_file(char *argv, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(argv, F_OK) == 0)
			printf("minishell: %s Is a directory\n", argv);
		else
			printf("minishell: no such file or directory: %s\n", argv);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

int	find_path_env(void)
{
	int	i;

	i = 0;
	while (g_msh.env[i] && ft_strnstr(g_msh.env[i], "PATH", 4) == 0)
		i++;
	return (i);
}

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = find_path_env();
	if (g_msh.env[i] == NULL)
		error(cmd, 1);
	paths = ft_split(g_msh.env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
	}
	free(path);
	ft_free_tab(paths);
	return (NULL);
}

void	free_fd(t_job *first)
{
	while (first)
	{
		close(first->fd[0]);
		close(first->fd[1]);
		first = first->next;
	}
}
