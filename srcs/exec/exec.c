/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/19 15:51:44 by gcollet          ###   ########.fr       */
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

void	child_process(t_job *job, t_job *first)
{
	g_msh.switch_signal = 1;
	job->pid = fork();
	if (job->pid == -1)
		printf("Dang! This fork didn't work!");
	if (job->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (job->previous != NULL)
			dup2(job->previous->fd[0], STDIN_FILENO);
		if (job->next != NULL)
			dup2(job->fd[1], STDOUT_FILENO);
		check_redirection(job);
		close(job->fd[0]);
		close(job->fd[1]);
		free_fd(first);
		if (ms_builtins(job->cmd, 1) == 1)
			execute(job->cmd);
	}
	if (job->previous != NULL)
		close(job->previous->fd[0]);
	close(job->fd[1]);
/* 	if (job->next != NULL)
		close(job->fd[0]); */
}

int	ms_exec_builtins(t_job *job)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
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
	t_job	*first;
	int		status;

	first = job;
	init_pipe(first);
	if (make_heredocs(job) == 1 || ms_exec_builtins(job) == 1)
		return ;
	if (job->cmd)
	{
		while (job)
		{
			child_process(job, first);
			job = job->next;
			first = ms_head_list_job(first);
		}
		while (first)
		{
			waitpid(first->pid, &status, 0);
			if (WIFEXITED(status))
				g_msh.ret_exit = WEXITSTATUS(status);
			first = first->next;
		}
	}
	g_msh.switch_signal = 0;
}
