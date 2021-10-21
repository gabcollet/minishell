/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/10/21 10:19:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ms_get_path(void)
{
	char *path;
	
	if (!(path = getenv("PATH")))
		return (NULL);
	return (path);
}

/* Duplique l'env dans la variable global */
void	ms_dup_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	g_msh.env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while(env[++i])
		g_msh.env[i] = ft_strdup(env[i]);
	g_msh.env[i] = NULL;
	return ;
}

/* Trouve la ligne recherché par arg dans env et la retourne */
char	*ms_get_env(char *arg)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(arg);
	while (g_msh.env[i] && ft_strnstr(g_msh.env[i], arg, len) == 0)
			i++;
	if (g_msh.env[i] == NULL)
		return (NULL);
	return (g_msh.env[i]);
}

/* Remplace une ligne dans env par le nouveau contenue. Si la ligne n'existe pas en cree une nouvelle.
Arg devrait etre ex: HOME= et new content devrait etre ce qui va etre remplacer dedant. */
void	ms_set_env(const char *arg, const char *new_content)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(arg);
	while (arg && g_msh.env[i] && ft_strnstr(g_msh.env[i], arg, len) == 0)
		i++;
	if (g_msh.env[i] == NULL)
	{
		g_msh.env = ms_matrix_add_line(g_msh.env);
		g_msh.env[++i] = ft_strjoin(arg, new_content);
	}
	free(g_msh.env[i]);
	g_msh.env[i] = ft_strjoin(arg, new_content);
	return ;
}

size_t	ms_line_counter(char **env)
{
	size_t	count;

	count = 0;
	if (!env)
		return (0);
	while(env[count])
		count++;
	return (count);
}

// int main (int argc, char **argv, char **env)
// {
// 	(void)argc;
//  	(void)argv;
// 	ms_dup_arr(env);
// }
