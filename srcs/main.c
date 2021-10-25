/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/25 12:06:20 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct variabl globale
t_msh	g_msh;

void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	printf("\n******************************************");
	printf("\n\n\n\t    ****MINISHELL****");
	printf("\n\n-CRÉE PAR GABRIEL COLLET ET JUSTINE BADIA-");
	printf("\n\n\n******************************************");
	printf("\n\nUSER is: @%s\n\n", username);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		printf("tab[%i] = %s\n", i, tab[i]);
		i++;
	}
}

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
