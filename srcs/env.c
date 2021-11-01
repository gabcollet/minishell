/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/01 15:50:31 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Trouve la ligne recherché par arg dans env et la retourne 
sinon retourne NULL*/
char	*ms_get_env(char **env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (env[i] && ft_strnstr(env[i], arg, len) == 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

/* Remplace une ligne dans env par le nouveau contenue. Si la ligne n'existe
pas en cree une nouvelle. Arg devrait etre ex: HOME= et new content devrait 
etre ce qui va etre remplacer dedant. */
void	ms_set_env(char **env, char *value)
{
	int		i;
	int		len;
	char	**arg;

	i = 0;
	arg = ft_split(value, '=');
	len = ft_strlen(arg[0]);
	while (env[i] && ft_strnstr(env[i], arg[0], len) == 0)
		i++;
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
	return ;
}
