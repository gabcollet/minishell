/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/17 15:44:39 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd)
{
	char	*path;

	execve(cmd[0], cmd, g_msh.env);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(cmd[0], F_OK) == 0)
			error(cmd[0], 2);
		error(cmd[0], 1);
	}
	path = find_path(cmd[0]);
	if (path && (execve(path, cmd, g_msh.env) == -1))
		error(cmd[0], 0);
	error(cmd[0], 0);
}

void	parent_process(t_job *job)
{
	int		wstatus;

	wstatus = 0;
	job->pid = fork();
	if (job->pid == -1)
		printf("Dang! This fork didn't work!");
	if (job->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		check_redirection(job);
		if (ms_builtins(job->cmd, 1) == 1)
			execute(job->cmd);
	}
}

void	child_process(t_job *job)
{
	int		status;

	status = 0;
	job->pid = fork();
	if (job->pid == -1)
		printf("Dang! This fork didn't work!");
	if (job->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(job->fd[0]);
		dup2(job->fd[1], STDOUT_FILENO);
		check_redirection(job);
		if (ms_builtins(job->cmd, 1) == 1)
			execute(job->cmd);
	}
	close(job->fd[1]);
	dup2(job->fd[0], STDIN_FILENO);
}

int	ms_exec_builtins(t_job *job, int saved_stdin, int saved_stdout)
{
	if (job->next == NULL)
	{
		if (check_builtins(job->cmd) == 1)
			return (0);
		check_redirection(job);
		if (ms_builtins(job->cmd, 0) == 0)
		{
			restore_fd(saved_stdin, saved_stdout);
			return (1);
		}
	}
	return (0);
}

void	ms_exec(t_job *job)
{
	int		saved_stdin;
	int		saved_stdout;
	t_job	*first;
	t_job	*first1;
	int		status;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	first = job;
	first1 = job;
	init_pipe(first);
	if (make_heredocs(job) == 1)
		return ;
	if (ms_exec_builtins(job, saved_stdin, saved_stdout) == 1)
		return ;
	g_msh.switch_signal = 1;
	if (job->cmd)
	{
		while (job->next)
		{
			child_process(job);
			job = job->next;
		}
		parent_process(job);
		while (first1)
		{
			waitpid(first->pid, &status, 0);
			if (WIFEXITED(status))
				g_msh.ret_exit = WEXITSTATUS(status);
			first1 = first1->next;
		}
		restore_fd(saved_stdin, saved_stdout);
	}
	g_msh.switch_signal = 0;
	return ;
}
