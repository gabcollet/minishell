/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/15 16:42:20 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

void	loop()
{
	char	*line;
	t_job	*job_first;

	line = NULL;
	while (true)
	{
		if (line != NULL)
			free(line);
		line = readline("\001\e[1;96m\002minishell 1.1$ \001\033[0m\002");
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (*line)
		{
			add_history(line);
			job_first = ms_parsing(line, job_first);
			ms_exec(job_first);
		}
	}
	free(line);
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*token;
	t_job	*job_first = NULL;

	(void)argc;
	/* init_shell(); */
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
	ft_free_tab(g_msh.env);
	ft_free_tab(g_msh.env_export);
}
