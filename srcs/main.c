/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/02 13:59:22 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

int	look_for_pipe_or_redir(char *parsing)
{
	if (ft_strchr(parsing, '|') != NULL || ft_strchr(parsing, '<') != NULL
		|| ft_strchr(parsing, '>') != NULL || ft_strcmp(parsing, "<<") == 0
		|| ft_strcmp(parsing, ">>") == 0)
		return (1);
	return (0);
}

void	loop(void)
{
	char	*line;
	char**	temp_parsing;
	int		i;

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
		/* ms_parsing(line); */
		temp_parsing = ft_split(line, ' ');
		i = 0;
		while (temp_parsing[i])
		{
			if (look_for_pipe_or_redir(temp_parsing[i]) == 1)
			{	
				ms_exec(temp_parsing);
				break;
			}
			i++;
			if (temp_parsing[i] == NULL && ms_builtins(temp_parsing) == 1)
				ms_exec(temp_parsing);
		}
		ft_free_tab(temp_parsing);
	}
	free(line);
}

void	ctrl_c(int var)
{
	(void) var;
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
