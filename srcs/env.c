/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/26 15:36:29 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Trouve la ligne recherché par arg dans env et la retourne 
sinon retourne NULL*/
char	*ms_get_env(char **env, char *arg)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

/*Va chercher la variable d'env selon le nom de arg et retournes 
l'expansion de la variable sans son nom ou retournes NULL*/
char	*ms_get_varenv(char **env, char *arg)
{
	int		i;
	char	**split;
	char	*var_env;

	i = 0;
	var_env = NULL;
	while (env[i] && !var_env)
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
			var_env = ft_strdup(split[1]);
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (var_env);
}

int	env_compare(char **env, char **arg, int i)
{
	char	**split;

	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg[0]) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		i++;
		ft_free_tab(split);
	}
	return (i);
}

/* Remplace une ligne dans env par le nouveau contenue. Si la ligne n'existe
pas en cree une nouvelle. Arg devrait etre ex: HOME= et new content devrait 
etre ce qui va etre remplacer dedans. */
void	ms_set_env(char **env, char *value)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(value, '=');
	i = env_compare(env, arg, i);
	if (env[i] == NULL)
	{
		g_msh.env = ms_matrix_add_line(env, value);
		ft_free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_tab(arg);
}
