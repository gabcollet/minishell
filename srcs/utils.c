/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:07:55 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/26 14:08:22 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cree une nouvelle matrix en ajoutant une ligne et free l'ancienne */
char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (matrix[++i])
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i] = ft_strdup(new_line);
	i++;
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

/* Cree une nouvelle matrix en retirant une ligne et free l'ancienne */
char	**ms_matrix_remove_line(char **matrix, char *line)
{
	int		i;
	int		j;
	char	**new_matrix;

	i = 0;
	j = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (matrix[++i])
	{
		if (ft_strcmp(matrix[i], line) == 0)
			i++;
		if (matrix[i])
			new_matrix[j++] = ft_strdup(matrix[i]);
	}
	new_matrix[j] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

size_t	ms_line_counter(char **env)
{
	size_t	count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
		count++;
	return (count);
}
