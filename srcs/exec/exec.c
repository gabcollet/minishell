/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/01 17:07:18 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one or NULL. */
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

/* Function that try exec or take the command and send it to find_path
 before executing it. */
void	execute(char *arg)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
	execve(cmd[0], cmd, g_msh.env);
	if (ft_strchr(cmd[0], '/') != NULL)
		error(cmd[0], 1);
	if (execve(find_path(cmd[0]), cmd, g_msh.env) == -1)
		error(cmd[0], 0);
}

void	parent_process(char *arg)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork did'nt work!");
	if (pid == 0)
		execute(arg);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_msh.ret_exit = WEXITSTATUS(status);
	}
}

void	child_process(char *arg)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	status = 0;
	if (pipe(fd) == -1)
		printf("Dang! This pipe did'nt work!");
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork did'nt work!");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		/* if (ms_builtins(arg) == 0); */ //cd export pi unset ne fonctionneront pas dememe
		execute(arg);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_msh.ret_exit = WEXITSTATUS(status);
	}
}

/* ls -la | echo $PATH > test.txt */
/* <ls> <-la> <|> <echo> </Users/gcollet/homebrew/bin:...> <>> <test.txt> <NULL>*/
/* <ls -la> <echo /Users/gcollet/homebrew/bin:...> < > test.txt> <NULL> */

void	ms_exec(char **arg)
{
	int	i;
	int	saved_stdin;
	/* int	filein;
	int	fileout; */

	i = 0;
	g_msh.switch_signal = 1;
	saved_stdin = dup(0);
	arg = make_command(arg);
	/* while (arg[i])
		printf("%s\n", arg[i++]);
	i = 0; */
	if (arg)
	{
		/* partie qui open si ca pipe */
		/* if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(arg[argc - 1], 1);
			filein = open_file(arg[1], 2);
			dup2(filein, STDIN_FILENO);
		} */
		while (arg[i + 1])
			child_process(arg[i++]);
		parent_process(arg[i]);
		dup2(saved_stdin, 0);
		close(saved_stdin);
	}
	g_msh.switch_signal = 0;
	return ;
}
