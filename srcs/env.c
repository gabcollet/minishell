/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/10/19 19:07:29 by jbadia           ###   ########.fr       */
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

// quand on imprime env, il faudra partir en index 1 !!!!
char **ms_dup_arr(char **arr)
{
	char	**str;
	size_t		i;
	size_t			j;

	i = ms_line_counter(arr);
	j = 0;
	str = ft_calloc(i + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (arr[j] && j < i)
	{
		str[j] = ft_strdup(arr[j]);
		if (!str[j])
			ft_free_tab(&str[j]);
		j++;
	}
	return (str);
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
