/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/29 11:01:10 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd, t_job *job)
{
	char	*path;

	execve(cmd[0], cmd, g_msh.env);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(cmd[0], F_OK) == 0)
			error(cmd[0], 2, job);
		error(cmd[0], 1, job);
	}
	path = find_path(cmd[0], job);
	if (path && (execve(path, cmd, g_msh.env) == -1))
		error(cmd[0], 0, job);
	error(cmd[0], 0, job);
}

void	child_process(t_job *job, t_job *first)
{
	g_msh.switch_signal = 1;
	signal(SIGINT, nothing);
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
		check_redirection(job, 0);
		close(job->fd[0]);
		close(job->fd[1]);
		free_fd(first);
		if (job->cmd && ms_builtins(job->cmd, 1, first) == 1)
			execute(job->cmd, first);
	}
	if (job->previous != NULL)
		close(job->previous->fd[0]);
	close(job->fd[1]);
}

int	ms_exec_builtins(t_job *job)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (job && job->next == NULL)
	{
		if (job->cmd && check_builtins(job->cmd) == 1)
			return (0);
		if (check_redirection(job, 1) == 1)
			return (1);
		if (ms_builtins(job->cmd, 0, job) == 0)
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
	if (job && job->cmd)
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
