/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:07:55 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/20 15:15:45 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cree une nouvelle matrix en ajoutant une ligne et free l'ancienne */
char	**ms_matrix_add_line(char **matrix)
{
	int i;
	char **new_matrix;
	
	i = 0;
	while (g_msh.env[i])
		i++;
	new_matrix = malloc(sizeof(char *) * i + 1);
	i = -1;
	while(matrix[++i])
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}
