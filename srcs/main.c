/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:49:24 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/14 15:20:37 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	c[PATH_MAX];
	char	*line;

	while (true)
	{
		line = readline("minishell 1.0: ");
		if (ft_strcmp(line, "pwd") == 0)
		{
			getcwd(c, sizeof(c));
			printf("%s\n", c);
		}
		if (ft_strncmp(line, "echo", 3) == 0)
			printf("%s\n", line + 5);
		else if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			printf("exit\n");
			break ;
		}
	}
}
