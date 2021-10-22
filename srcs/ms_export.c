/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:56:37 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/22 16:45:29 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
-	juste "export" affiche l'env en ordre ascii avec "declare -x " avant
-	sans = (export test1) | declare -x test1
-	avec un = (export test2=) (export test3=coucou) | declare -x test2="" declare -x test3="coucou"
-	plusieurs arguments (export test= o) | declare -x o declare -x test=""
-	peux pas commencer par un chiffre, ou signe qui n'est pas _
-	tu peux faire export de plusieurs variables sur une seule ligne et si 
	une est pas bonne tu arrete 
*/

char	*ms_make_string(char *arg)
{
	char	**strings;
	char	*string;
	char	*temp;
	
	strings = ft_split(arg, '=');
	temp = ft_strjoin(strings[0], "=\"");
	if (strings[1])
		string = ft_strjoin(temp, strings[1]);
	else
		string = ft_strdup(temp);
	free(temp);
	temp = ft_strjoin(string, "\"");
	free(string);
	ft_free_tab(strings);
	return (temp);
}

void	ms_export_sort(void)
{
	int	i;
	
	i = 0;
	ft_sort_tab(g_msh.env_export);
	while (g_msh.env_export[i])
		printf("declare -x %s\n", g_msh.env_export[i++]);
	return ;
}

int	ms_export(char **arg)
{
	int	i;
	char *string;

	i = 1;
	while (arg[i])
	{
		/* chek si l'arg est valide */
		if (ft_strchr(arg[i], '=') == NULL)
			g_msh.env_export = ms_matrix_add_line(g_msh.env_export, arg[i]);
		else
		{
			if (/* trouve une ligne avec le meme arg dans env_export */)
				/* remplace par l'arg soit dans env ou/et dans env_export*/
			else
			{	
				g_msh.env = ms_matrix_add_line(g_msh.env, arg[i]);
				string = ms_make_string(arg[i]);
				g_msh.env_export = ms_matrix_add_line(g_msh.env_export, string);
				free(string);
			}
		}
		i++;
	}
	if (arg[1] == NULL)
		ms_export_sort();
	return (0);
}

void	ms_init_export(void)
{
	int		i;

	i = 0;
	while (g_msh.env[++i])
		;
	/* je malloc un de moins car la derniere ligne est pas prise en compte */
	g_msh.env_export = malloc(sizeof(char *) * (i));
	i = 0;
	while (g_msh.env[i + 1])
	{
		g_msh.env_export[i] = ft_strdup(g_msh.env[i]);
		i++;
	}
	g_msh.env_export[i] = NULL;
	i = 0;
	/* while (g_msh.env_export[i])
		printf("declare -x %s\n", g_msh.env_export[i++]);
	printf("-----------------------\n"); */
}

t_msh g_msh;

int main(int ac, char** av, char **env)
{
	ac = 0;
	ms_dup_env(env);
	ms_init_export();
	ms_export(av);
	int	i = 0;
	while (g_msh.env_export[i])
		printf("declare -x %s\n", g_msh.env_export[i++]);
}
