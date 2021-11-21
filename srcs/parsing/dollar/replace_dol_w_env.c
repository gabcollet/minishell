/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dol_w_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:25:46 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/21 18:12:57 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remplace le $ENV par sa variable complète et retournes la nouvelle string*/
char	*replace_dol_w_env(char *token, t_dollar *dol)
{
	char	*temp;
	int		index;

	index = 0;
	temp = NULL;
	temp = ft_strdup(token);
	dol->str = ft_calloc((dollar_counter(token) + 1 + ft_strlen(token)),
			sizeof(char*));
	dol->index = 0;
	while (temp[index])
	{
		if (temp[index] == '\'' && dol->d_quote == 0)
			dol_s_quote(dol);
		else if (temp[index] == '\"' && dol->s_quote == 0)
			dol_d_quote(dol);
		else if (ft_strchr("$", temp[index]) && dol->s_quote == 0)
		{
			dol->name_var = get_arg(temp, index);
			if (!check_dol(dol->name_var))
				index = check_name_var(dol, index);
			else
				check_var_env(dol, temp, index);
			index += ft_strlen(dol->name_var) + 1;
			if (dol->name_var)
				free(dol->name_var);
			continue ;
		}
		dol->str[dol->index++] = temp[index++];
	}
	free(temp);
	return (dol->str);
}

void	dol_s_quote(t_dollar *dol)
{
	dol->s_quote++;
	if (dol->s_quote == 2)
		dol->s_quote = 0;
}

void	dol_d_quote(t_dollar *dol)
{
	dol->d_quote++;
	if (dol->d_quote == 2)
		dol->d_quote = 0;
}

int	check_name_var(t_dollar *dol, int i)
{
	int	j;
	int	k;

	k = 0;
	if (dol_solo(dol->name_var))
	{
		j = 0;
		i--;
	}
	else
		j = 1;
	while (dol->name_var[k++])
		dol->str[dol->index++] = dol->name_var[j++];
	return (i);
}

void	check_var_env(t_dollar *dol, char *temp, int i)
{
	int		j;
	int 	k;
	char	**space;

	j = 0;
	k = 0;
	space = NULL;
	dol->var_env = ms_get_dolenv(temp, i);
	if (dol->var_env && dol->s_quote == 0 && dol->d_quote == 0)
	{
		space = ft_split(dol->var_env, ' ');
		while (space[k])
		{
			j = 0;
			while (space[k][j])
				dol->str[dol->index++] = space[k][j++];
			dol->str[dol->index++] = ' ';
			k++;
		}
	}
	//if (dol->var_env)
	else
	{
		while (dol->var_env[j])
			dol->str[dol->index++] = dol->var_env[j++];
	}
	free(dol->var_env);
	ft_free_tab(space);
}
