/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:40:30 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/28 17:19:45 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui valide le flag -n */
int	ms_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg[i++] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				break ;
			if (arg[i + 1] == '\0')
				return (true);
			i++;
		}
	}	
	return (false);
}

/* Echo the STRING(s) to standard output.
-n option doesn't output the trailing newline  */
int	ms_echo(char **arg)
{
	int	n;
	int	i;

	n = false;
	i = -1;
	while (ms_newline(arg[++i]))
		n = true;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	return (0);
}
