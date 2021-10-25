/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:56:37 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/25 11:33:35 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
-	juste "export" affiche l'env en ordre ascii avec "declare -x " avant
-	sans = (export test1) | declare -x test1
-	avec un = (export test2=) (export test3=coucou) | declare -x test2="" 
	declare -x test3="coucou"
-	plusieurs arguments (export test= o) | declare -x o declare -x test=""
-	peux pas commencer par un chiffre, ou signe qui n'est pas _
-	tu peux faire export de plusieurs variables sur une seule ligne et si 
	une est pas bonne tu arrete 
*/

// t_msh g_msh;

int	ms_check_export_arg(char *arg)
{
	if (ft_isalpha(arg[0]) == 0 && arg[0] != 95)
	{
		printf("export: '%s': not a valid identifier\n", arg);
		return (-1);
	}
	else
		return (0);
}

char	*ms_make_string(char *arg)
{
	char	**strings;
	char	*string;
	int		i;

	i = 1;
	strings = ft_split(arg, '=');
	string = ft_strjoin(strings[0], "=\"");
	while (strings[i] && strings[i + 1])
	{
		string = ft_strjoin_free_s1(string, strings[i++]);
		string = ft_strjoin_free_s1(string, "=");
	}
	if (strings[i])
		string = ft_strjoin_free_s1(string, strings[i]);
	string = ft_strjoin_free_s1(string, "\"");
	ft_free_tab(strings);
	return (string);
}

void	ms_export_sort(void)
{
	int	i;

	i = 0;
	ft_sort_tab(g_msh.env_export);
	while (g_msh.env_export[i])
		printf("declare -x %s\n", g_msh.env_export[i++]);
}

void	ms_export_valid_arg(char *arg, char *strings)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(g_msh.env_export, strings) == NULL)
			g_msh.env_export = ms_matrix_add_line(g_msh.env_export, arg);
	}
	else
	{
		string = ms_make_string(arg);
		if (ms_get_env(g_msh.env_export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(g_msh.env, arg);
			ms_set_env(g_msh.env_export, string);
			free(arg);
		}
		else
		{	
			g_msh.env = ms_matrix_add_line(g_msh.env, arg);
			g_msh.env_export = ms_matrix_add_line(g_msh.env_export, string);
		}
		free(string);
	}
}

int	ms_export(char **arg)
{
	char	**strings;
	int		i;

	i = 1;
	while (arg[i] && ms_check_export_arg(arg[i]) == 0)
	{	
		strings = ft_split(arg[i], '=');
		ms_export_valid_arg(arg[i], strings[0]);
		ft_free_tab(strings);
		i++;
	}
	if (arg[1] == NULL)
		ms_export_sort();
	return (0);
}

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

// int main(int ac, char** av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	ms_dup_env(env);
// 	ms_init_export();
// 	ms_export(av);
// 	/* int	i = 0;
// 	while (g_msh.env[i])
// 		printf("declare -x %s\n", g_msh.env[i++]); */
// 	ft_free_tab(g_msh.env);
// 	ft_free_tab(g_msh.env_export);
// }
