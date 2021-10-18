/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/18 17:11:21 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct variabl globale
t_msh g_msh;

void init_shell()
{
    printf("\n******************************************");
    printf("\n\n\n\t    ****MINISHELL****");
    printf("\n\n-CRÉE PAR GABRIEL COLLET ET JUSTINE BADIA-");
    printf("\n\n\n******************************************");
    char* username = getenv("USER");
    printf("\n\nUSER is: @%s\n\n", username);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		printf("tab[%i] = %s\n",i,  tab[i]);
		i++;
	}
}

void	free_all(char *line, char **path)
{
	int i = 0;
	
	while (path[i])
		free (path[i++]);
	free (path);
	free(line);
}

int	main(int argc, char *argv[], char **env)
{
	char	c[PATH_MAX];
	char	*line;


	(void)argc;
	(void)argv;
	init_shell();
	line = NULL;

	ms_get_env(env);
	while (true)
	{
		if (line != NULL)
			free(line);
		line = readline("minishell 1.0: ");
		add_history(line);
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
	free(line);
	ft_free_struct(&g_msh);
}
