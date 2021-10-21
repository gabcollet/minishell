/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:56:37 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/21 17:23:47 by gcollet          ###   ########.fr       */
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

/* Fonction qui trie les char * en ordre ascii  */
char	**ft_matrix_order(char **matrix)
{
	char	**new_matrix;
	char	*temp;
	int		len;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (matrix[len])
		len++; //compte la longeur de la matrix dans len
	new_matrix = malloc(sizeof(char *) * (len + 1));
	while (j != len)
	{
		i = 0;
		while (matrix[i] && matrix[i][0] == 0)
		{
			i++;	
			continue ;
		}
		temp = matrix[i];
		if (temp == NULL)
			break ;
		i = 0;
		while (i < len)
		{
			if (matrix[i][0] != 0 && ft_strcmp(temp, matrix[i]) > 0)
				temp = matrix[i];
			i++;
		}
		new_matrix[j] = ft_strdup(temp);
		temp[0] = 0;
		j++;
	}
	new_matrix[j] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}
/* insertion sort */
/* static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_strarr_sort(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
				swap(&arr[i], &arr[j]);
			++j;
		}
		++i;
	}
} */
/* -malloc un tableau de char* de la bonne len
-en chekant tout les char* trouver le plus petit qui reste
-ajouter le declare -x
-mettre le char* sur la 1ere ligne du nouveau tableau */

void	ms_export_dup_env(char **env)
{
	int		i;
	char	**temp;
	char	**env_copy;

	i = 0;
	while (env[++i])
	env_copy = malloc(sizeof(char *) * (i + 1));
	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(env[i])
	{
		temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = NULL;
	/* mettre en ordre */
	env_copy = ft_matrix_order(temp);
	/* ft_strarr_sort(temp); */
	i = 0;
	while (temp[i])
 		printf("declare -x %s\n", temp[i++]);
	/* while (temp[i])
 		printf("%s\n", temp[i++]); */
	ft_free_tab(env_copy);
	return ;
}

int	ms_export(char **arg)
{
	if (arg)
		arg=NULL; //do something
	else
		ms_export_dup_env(g_msh.env);
	return (0);
}

t_msh g_msh;

int main(int ac, char** av, char **env)
{
	ac = 0;
	av = NULL;
	ms_dup_env(env);
	ms_export(NULL);
}
