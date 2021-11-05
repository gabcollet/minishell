/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:37:01 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/05 15:46:48 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Display error and quit the child process */
void	error(char *arg, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	exit (127);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	/* write and append (>>) */
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	/* write and trunc (>) */
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	/* read only (<) */
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		printf("minishell: no such file or directory: %s", argv);
	return (file);
}

int	count_pipe(char **arg)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

/* char	*make_command_string(char *string, char **arg)
{
	while (arg[g_msh.cmd_i][0] != '|')
	{
		if (arg[g_msh.cmd_i] == NULL)
			break;
		if ((arg[g_msh.cmd_i + 1] == NULL || arg[g_msh.cmd_i + 1][0] == '|')
			&& string == NULL)
			string = ft_strjoin(arg[g_msh.cmd_i], " ");
		else if (string == NULL)
		{
			string = ft_strjoin(arg[g_msh.cmd_i], " ");
			string = ft_strjoin_free_s1(string, arg[g_msh.cmd_i + 1]);
			g_msh.cmd_i++;
		}
		else
			string = ft_strjoin_free_s1(string, arg[g_msh.cmd_i]);
		g_msh.cmd_i++;
		string = ft_strjoin_free_s1(string, " ");
		if (arg[g_msh.cmd_i] == NULL)
			break ;
	}
	g_msh.cmd_i++;
	return (string);
}

char	**make_command(char **arg)
{
	int		count;
	int		k;
	char	**tab;
	char	*string;

	count = count_pipe(arg);
	k = 0;
	tab = malloc(sizeof(char *) * count + 2);
	g_msh.cmd_i = 0;
	while (count > 0)
	{
		string = NULL;
		string = make_command_string(string, arg);
		tab[k] = ft_strdup(string);
		free(string);
		k++;
		count--;
		printf("%d\n", i);
	}
	tab[k] = NULL;
	return (tab);
} */

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
/* void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
} */

/* Function that will read input from the terminal and return line. */
/* int	get_next_line(char **line)
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
} */
