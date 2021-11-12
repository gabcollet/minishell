/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/12 14:56:46 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parent_process(char **arg, char **redir, int *fd)
{
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork didn't work!");
	if (pid == 0)
	{
		check_redirection(redir, fd);
		if (ms_builtins(arg, 1) == 1)
			execute(arg);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_msh.ret_exit = WEXITSTATUS(wstatus);
}

void	child_process(char **arg, char **redir, int *fd_heredoc)
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
		check_redirection(redir, fd_heredoc);
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
	t_job *first;

	g_msh.switch_signal = 1;
	saved_stdin = dup(0);
	saved_stdout = dup(1);
	first = job;
	init_pipe(first);
	if (make_heredocs(job) == 1)
		return ;
	if (job->next == NULL)
	{
		check_redirection(job->file, job->fd);
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
			child_process(job->cmd, job->file, job->fd);
			job = job->next;
		}
		parent_process(job->cmd, job->file, job->fd);
		dup2(saved_stdin, 0);
		close(saved_stdin);
	}
	g_msh.switch_signal = 0;
	return ;
}
