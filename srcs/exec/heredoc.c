/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:15:25 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/12 10:52:17 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(char **redir, int stdin_fd)
{
	int 	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
			redir_heredoc(redir[++i], stdin_fd);
		i++;
	}
}

void	init_pipe(t_job *job)
{
	while (job)
	{
		pipe(job->fd);
		job = job->next;
	}
}

void	make_heredocs(t_job *job)
{
	while (job)
	{
		check_heredoc(job->file, job->fd[0]);
		job = job->next;
	}
}

void	redir_heredoc(char *limiter, int fd)
{
	int		new_fd[2];
	pid_t	pid;

	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd);
	waitpid(pid, NULL, 0);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
}

void	heredoc(char *limiter, int *fd)
{
	char *line;
	
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
	//gerer l'erreur si ya rien dans line
	free(line);
	exit(EXIT_SUCCESS);
}
