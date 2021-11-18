/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/18 15:08:24 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

t_msh	g_msh;

static char	*getcwd_dir(void)
{
	char		cwd[PATH_MAX];
	char		*home;
	char	*str;
	struct stat	buf;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup(""));
	home = ms_get_env(g_msh.env, "HOME=") + 5;
	if (home - 5 && ft_strnstr(cwd, home, ft_strlen(home)))
	{
		if (home[ft_strlen(home) - 1] == '/')
			return (ft_strdup(cwd));
		str = ft_strdup(home);
		str = ft_strjoin_free_s1(str, "/");
		str = ft_strjoin_free_s1(str, cwd + ft_strlen(home));
		if (stat(str, &buf) != -1)
		{
			free(str);
			return (ft_strjoin("~", cwd + ft_strlen(home)));
		}
	}
	return (ft_strdup(cwd));
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*dir;
	
	prompt = ft_strdup("\001\e[1;91m\002");
	if (g_msh.user)
		prompt = ft_strjoin_free_s1(prompt, g_msh.user);
	else
		prompt = ft_strjoin_free_s1(prompt, "tty");
	prompt = ft_strjoin_free_s1(prompt, "\001\033[0m\002:");
	dir = getcwd_dir();
	prompt = ft_strjoin_free_s1(prompt, "\001\e[1;96m\002");
	prompt = ft_strjoin_free_s1(prompt, dir);
	prompt = ft_strjoin_free_s1(prompt, "\001\033[0m\002$ ");
	free(dir);
	return (prompt);
}

void	loop(void)
{
	char	*line;
	t_job	*job_first;
	char *prompt;

	line = NULL;
	while (true)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (is_only_space(line))
			continue ;
		if (*line)
		{
			add_history(line);
			job_first = ms_parsing(line, job_first);
			free(line);
			ms_exec(job_first);
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*token;
	t_job	*job_first = NULL;

	(void)argc;
	init_shell();
	token = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (argv[1] && ft_strcmp(argv[1], "-c") == 0)
	{
		job_first = ms_parsing(argv[2], job_first);
		ms_exec(job_first);
		return (0);
	}
	loop();
}
