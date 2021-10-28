/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:33:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/28 17:01:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one or NULL. */
char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(g_msh.env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(g_msh.env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

/* Display error and quit the child process */
void	error(char *arg, int i)
{
	if (i == 0)
		printf("minishell: %s: command not found\n", arg);
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	exit (127);
}

/* Function that try exec or take the command and send it to find_path
 before executing it. */
void	execute(char **arg)
{
	execve(arg[0], NULL, g_msh.env);
	if (ft_strchr(arg[0], '/') != NULL)
		error(arg[0], 1);
	if (execve(find_path(arg[0]), arg, g_msh.env) == -1)
		error(arg[0], 0);
}

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


void	child_process(char **arg)
{
	pid_t	pid;
	int		status;
	/* int		fd[2]; */

	status = 0;
	/* if (pipe(fd) == -1)
		error(); */
	pid = fork();
	if (pid == -1)
		printf("Dang! This fork did'nt work!");
	if (pid == 0)
	{
		/* close(fd[0]);
		dup2(fd[1], STDOUT_FILENO); */
		execute(arg);
	}
	else
	{
		/* close(fd[1]);
		dup2(fd[0], STDIN_FILENO); */
		waitpid(pid, &status, 0); 
		if (WIFEXITED(status))
			g_msh.ret_exit = WEXITSTATUS(status);
		/* printf("%d\n", g_msh.ret_exit); */
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	/* if (file == -1)
		erreur d'ouverture de file */
	return (file);
}

/* <ls> <-la> */

void	ms_exec(char **arg)
{
	int	i;
	/* int	filein;
	int	fileout; */

	i = 0;
	if (arg)
	{
		/* partie qui open si ca pipe */
		/* if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(arg[argc - 1], 1);
			filein = open_file(arg[1], 2);
			dup2(filein, STDIN_FILENO);
		} */
		child_process(arg);
		/* dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp); */
	}
	return ;
}