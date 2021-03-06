/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dol_w_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:25:46 by jbadia            #+#    #+#             */
/*   Updated: 2021/12/08 10:03:52 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remplace le $ENV par sa variable complète et retournes la nouvelle string*/
char	*replace_dol_w_env(char *tok, t_dollar *dol)
{
	char	*temp;
	int		index;

	index = 0;
	temp = ft_strdup(tok);
	dol->str = ft_calloc((dol_c(tok, dol) + ft_strlen(tok)), sizeof(char));
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
			index = handle_dol_var(dol, temp, index);
			index += ft_strlen(dol->name_var) + 1;
			ft_free(dol->name_var);
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

	if (dol_solo(dol->name_var))
	{
		j = 0;
		i--;
	}
	else
		j = 1;
	while (dol->name_var[j])
		dol->str[dol->index++] = dol->name_var[j++];
	return (i);
}

void	check_var_env(t_dollar *dol, char *temp, int i)
{
	int		j;

	j = 0;
	dol->var_env = ms_get_dolenv(temp, i);
	if (dol->var_env && dol->s_quote == 0 && dol->d_quote == 0)
	{
		copy_arr_tab(dol);
		dol->type = STRING;
	}	
	else if (dol->var_env)
	{
		while (dol->var_env[j])
			dol->str[dol->index++] = dol->var_env[j++];
		dol->type = STRING;
	}
	if (!dol->var_env && dol->type != STRING)
		dol->type = VOID;
	free(dol->var_env);
}
