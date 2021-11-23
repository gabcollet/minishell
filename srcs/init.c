/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:05:15 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/23 14:14:40 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_shlvl(void)
{
	char	*var;
	char	*var1;
	int		num;
	char	**arg;

	var = ms_get_env(g_msh.env, "SHLVL");
	if (var == NULL)
	{
		g_msh.env = ms_matrix_add_line(g_msh.env, "SHLVL=1");
		return ;
	}
	arg = ft_split(var, '=');
	num = ft_atoi(arg[1]);
	num++;
	var = ft_itoa(num);
	var1 = ft_strjoin("SHLVL=", var);
	ms_set_env(g_msh.env, var1);
	free (var);
	free (var1);
	ft_free_tab(arg);
	return ;
}

/* Duplique l'env dans la variable global */
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
	check_shlvl();
	return ;
}

/* sert à initier le tableau d'env_export */
void	ms_init_export(void)
{
	int		i;
	char	*string;

	i = 0;
	while (g_msh.env[i])
		i++;
	g_msh.env_export = malloc(sizeof(char *) * (i));
	i = 0;
	if (g_msh.env[i])
	{
		while (g_msh.env[i + 1])
		{
			string = ms_make_string(g_msh.env[i]);
			g_msh.env_export[i] = ft_strdup(string);
			free(string);
			i++;
		}
	}
	g_msh.env_export[i] = NULL;
}

void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	if (username)
		g_msh.user = ft_strdup(username);
	else
		g_msh.user = NULL;
	printf("\e[2J\e[H\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n");
	printf("\e[91m███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\e[0m\n");
	printf("\e[1;96mMade by: JUSTINE BADIA & GABRIEL COLLET\e[0m\n");
	printf("\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n");
	printf("\nWelcome %s\n", username);
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
