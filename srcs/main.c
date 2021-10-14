/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/14 15:57:40 by gcollet          ###   ########.fr       */
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

int	main(void)
{
	char	c[PATH_MAX];
	char	*line;

	init_shell();
	while (true)
	{
		line = readline("minishell 1.0: ");
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
			free(line);
			printf("exit\n");
			break ;
		}
	}
}
