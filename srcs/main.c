/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/15 11:48:27 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell()
{
    printf("\n******************"
        "************************");
    printf("\n\n\n\t    ****MINISHELL****");
    printf("\n\n-CRÉE PAR GABRIEL COLLET ET JUSTINE BADIA-");
    printf("\n\n\n*******************"
        "***********************");
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


int	main(int argc, char *argv[], char **env)
{
	char	c[PATH_MAX];
	char	*line;
	char	*p_path;
	char 	**path;
	char	**parsing;

	(void)argc;
	(void)argv;
	(void)env;
	init_shell();
	p_path = get_path();
	path = ft_split(p_path, ':');
	

	while (true)
	{
		line = readline("minishell 1.0: ");
		parsing = ft_split(line, ' ');
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
			print_tab(path);
		else if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			printf("exit\n");
			break ;
		}
	}
}
