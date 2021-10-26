/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 18:32:57 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct variabl globale
t_msh	g_msh;

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_token	*token;
	char** temp_parsing;

	(void)argc;
	(void)argv;
	init_shell();
	line = NULL;
	token = NULL;
	ms_init_env(env);
	ms_init_export();
	g_msh.ret_exit = 0;
	while (true)
	{
		if (line != NULL)
			free(line);
		line = readline("\033[32m\033[1mminishell 1.0: \033[0m");
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (*line)
			add_history(line);
		else
			continue ;
		/* ms_parsing(line); */
		temp_parsing = ft_split(line, ' ');
		ms_builtins(temp_parsing);
		ft_free_tab(temp_parsing);
	}
	free_all(line, g_msh.env);
}
