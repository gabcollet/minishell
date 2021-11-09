/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/09 13:31:00 by gcollet          ###   ########.fr       */
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
void	execute(char **cmd)
{
	execve(cmd[0], cmd, g_msh.env); //error is a directory
	if (ft_strchr(cmd[0], '/') != NULL)
		error(cmd[0], 1);
	if (execve(find_path(cmd[0]), cmd, g_msh.env) == -1)
		error(cmd[0], 0);
}

/* int	redir_output()
{
	int	fileout;

	if (g_msh.redir_output != NULL)
		return (fileout = open_file(g_msh.redir_output, 1));
	else if (g_msh.append_output != NULL)
		return (fileout = open_file(g_msh.append_output, 0));
	return (0);
} */

void	parent_process(char **arg, char	**redir)
{
	pid_t	pid;
	int		wstatus;
	int		fd[2];
	int 	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	wstatus = 0;
/* 	while (redir && redir[i])
	{
		printf("%s\n", redir[i]);
		i++;
	}
	printf("-----------------------------\n");
	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	i = 0; */
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<") == 0)
			fd[0] = open_file(redir[++i], 2);
		else if (ft_strcmp(redir[i], ">") == 0)
			fd[1] = open_file(redir[++i], 1);
		else if (ft_strcmp(redir[i], ">>") == 0)
			fd[1] = open_file(redir[++i], 0);
		i++;
	}
	if (pid == 0)
	{
		if (fd[0])
			dup2(fd[0], STDIN_FILENO);
		if (fd[1])
			dup2(fd[1], STDOUT_FILENO);
		if (ms_builtins(arg, 1) == 1)
			execute(arg);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_msh.ret_exit = WEXITSTATUS(wstatus);
}

void	child_process(char **arg)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	status = 0;
	if (pipe(fd) == -1)
		printf("Dang! This pipe didn't work!");
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (ms_builtins(arg, 1) == 1)
			execute(arg);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_msh.ret_exit = WEXITSTATUS(status);

}

void	ms_exec(t_job *job)
{
	int	saved_stdin;

	g_msh.switch_signal = 1;
	saved_stdin = dup(0);
	if (job->cmd)
	{
		while (job->next)
		{
			child_process(job->cmd);
			job = job->next;
		}
		parent_process(job->cmd, job->redir->file);
// Important pour que le readline refonctionne apres
		dup2(saved_stdin, 0);
		close(saved_stdin);
	}
	g_msh.switch_signal = 0;
	return ;
}

/* pour les redirection:
check si les redirections sont a NULL
sinon open le file mentionner
dup2 le file open au bon stdin 
ramene le saved_stdin

pour le here doc:
same mais tu prend les inputs dans le get_next_line

est-ce que le pipe prend le dsessus sur la redir ou l'inverse? */