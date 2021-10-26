/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:05:15 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 14:22:38 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Duplique l'env dans la variable global */
/* a mettre plus general et mettre dans la libft */
void	ms_init_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_msh.env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		g_msh.env[i] = ft_strdup(env[i]);
	g_msh.env[i] = NULL;
	return ;
}

/* sert à initier le tableau d'env_export */
void	ms_init_export(void)
{
	int		i;
	char	*string;

	i = 0;
	while (g_msh.env[++i])
		;
	g_msh.env_export = malloc(sizeof(char *) * (i));
	i = 0;
	while (g_msh.env[i + 2])
	{
		string = ms_make_string(g_msh.env[i]);
		g_msh.env_export[i] = ft_strdup(string);
		free(string);
		i++;
	}
	g_msh.env_export[i] = NULL;
}

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

char	*ms_init_s_parser(t_parser *parser, char *line)
{
	char	*temp;
	char	*str;

	parser->index = 0;
	parser->state = TEXT;
	temp = ft_strdup(line);
	str = temp;
	str = ms_trim_space(temp);
	free(temp);
	parser->str_line = str;
	free(line);
	return (str);
}
