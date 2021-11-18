/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:15:25 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/18 13:17:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredocs(t_job *job)
{
	while (job)
	{
		if (check_heredoc(job->file, job->fd[0]) == 1)
			return (1);
		job = job->next;
	}
	return (0);
}

int	check_heredoc(char **redir, int stdin_fd)
{
	int	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
		{
			if (redir_heredoc(redir[++i], stdin_fd) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_heredoc(char *limiter, int fd)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, nothing);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_msh.ret_exit = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

void	heredoc(char *limiter, int *fd)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	exit(EXIT_SUCCESS);
}

void	init_pipe(t_job *job)
{
	while (job)
	{
		pipe(job->fd);
		job = job->next;
	}
}
