/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 15:11:25 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct variabl globale
t_msh	g_msh;

int	main(int argc, char *argv[], char **env)
{
	char	c[PATH_MAX];
	char	*line;
	t_token	*token;

	(void)argc;
	(void)argv;
	init_shell();
	line = NULL;
	token = NULL;
	ms_init_env(env);
	while (true)
	{
		if (line != NULL)
			free(line);
		line = readline("minishell 1.0: ");
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (*line)
			add_history(line);
		else
			continue ;
		ms_parsing(line); 
	}
	free_all(line, g_msh.env);
}
