/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/11 11:08:32 by gcollet          ###   ########.fr       */
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

void	parent_process(char **arg, char **redir)
{
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
	{
		check_redirection(redir);
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
	int	saved_stdout;

	g_msh.switch_signal = 1;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (job->next == NULL)
	{
		check_redirection(job->file);
	 	if (ms_builtins(job->cmd, 0) == 0)
		{
			dup2(saved_stdin, 0);
			close(saved_stdin);
			dup2(saved_stdout, 1);
			close(saved_stdout);
			return ;
		}
	}
	if (job->cmd)
	{
		while (job->next)
		{
			child_process(job->cmd);
			job = job->next;
		}
		parent_process(job->cmd, job->file);
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