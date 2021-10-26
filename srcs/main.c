/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 14:14:19 by gcollet          ###   ########.fr       */
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
	g_msh.env = ms_dup_arr(env);
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
		//ft_strtrim(line, WHITESPACE);
		if (*line)
			add_history(line);
		else
			continue ;
		ms_parsing(line); 

		if (ft_strcmp(line, "pwd") == 0)
		{
			getcwd(c, sizeof(c));
			printf("%s\n", c);
		}
		//il faudrait passé un ft_split sur les args et juste checker le 1er au lieu de strncmp
		else if (ft_strncmp(line, "echo", 4) == 0)
			printf("%s\n", line + 5); 
		else if (ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
	}
	free_all(line, g_msh.env);
}
