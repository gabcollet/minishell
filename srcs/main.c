/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/15 18:20:33 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell()
{
    printf("\n******************************************");
    printf("\n\n\n\t    ****MINISHELL****");
    printf("\n\n-CRÉE PAR GABRIEL COLLET ET JUSTINE BADIA-");
    printf("\n\n\n******************************************");
    char* username = getenv("USER");
    printf("\n\nUSER is: @%s\n\n", username);
}

char *get_path(void)
{
	char *path;
	
	if (!(path = getenv("PATH")))
		return (NULL);
	return(path);
}

void	print_tab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != 0)
	{
		printf("%s\n", tab[i]);
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
	char	*p_path;
	char 	**path;
	char	**tab_env;

	(void)argc;
	(void)argv;
	(void)env;
	init_shell();
	p_path = get_path();
	tab_env = env; //mettre la variable env dans une autres pour pouvoir la modifier plus tard
	path = ft_split(p_path, ':');
	line = NULL;
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
		else if (ft_strncmp(line, "env", 3) == 0)
			print_tab(tab_env);
		else if (ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
	}
	free_all(line, path);
}
