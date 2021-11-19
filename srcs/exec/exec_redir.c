/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:13:49 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/19 09:46:39 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection(t_job *job)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	while (job->file && job->file[i])
	{
		if (ft_strcmp(job->file[i], "<") == 0)
			fd[0] = open_file(job->file[++i], 2);
		else if (ft_strcmp(job->file[i], ">") == 0)
			fd[1] = open_file(job->file[++i], 1);
		else if (ft_strcmp(job->file[i], ">>") == 0)
			fd[1] = open_file(job->file[++i], 0);
		else if (ft_strcmp(job->file[i], "<<") == 0)
			dup2(job->fd[0], STDIN_FILENO);
		i++;
	}
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}
