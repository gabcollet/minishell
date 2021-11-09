/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/09 13:21:19 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

void	loop(void)
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
			add_history(line);

		job_first = ms_parsing(line, job_first);
		if (job_first->next == NULL)
		{
			//ne pas oublier les redirs pour les builtins
			if (ms_builtins(job_first->cmd, 0) == 1)
				ms_exec(job_first);
		}
		/* else
			ms_exec(job_first); */
	}
	free(line);
}

void	ctrl_c(int var)
{
	(void) var;
	if (g_msh.switch_signal == 0)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_msh.switch_signal == 0)
		rl_redisplay();
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*token;

	(void)argc;
	(void)argv;
	init_shell();
	token = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	loop();
	ft_free_tab(g_msh.env);
	ft_free_tab(g_msh.env_export);
}
