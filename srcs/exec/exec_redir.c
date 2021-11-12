/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:13:49 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/12 12:09:48 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection(char **redir, int *fd_pipe)
{
	int		fd[2];
	int 	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<") == 0)
			fd[0] = open_file(redir[++i], 2);
		else if (ft_strcmp(redir[i], ">") == 0)
			fd[1] = open_file(redir[++i], 1);
		else if (ft_strcmp(redir[i], ">>") == 0)
			fd[1] = open_file(redir[++i], 0);
		else if (ft_strcmp(redir[i], "<<") == 0)
			dup2(fd_pipe[0], STDIN_FILENO);
		i++;
	}
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
}