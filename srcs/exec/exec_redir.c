/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:13:49 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/11 12:11:02 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection(char **redir)
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
			fd[0] = here_doc(redir[++i], fd);
		i++;
	}
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
}

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
int	here_doc(char *limiter, int *fd)
{
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		printf("Dang! This pipe didn't work!");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	close(fd[1]);
	wait(NULL);
	return (fd[0]);
}

/* Function that will read input from the terminal and return line. */
int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
