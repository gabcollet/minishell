/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:40:08 by jbadia            #+#    #+#             */
/*   Updated: 2021/12/03 12:06:37 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*vérifie sur la string qui suit $ est valide: 
ne commence pas par un chiffre 
et ne contient que des caractères alphanum ou _*/
bool	check_dol(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[0]))
			return (false);
		else if (ft_strchr("_", tab[i]) || ft_strchr("\'", tab[i])
			|| ft_strchr("\"", tab[i]) || ft_isdigit(tab[i])
			|| ft_strchr("?", tab[i]))
			i++;
		else if (!ft_isalnum(tab[i]))
			return (false);
		i++;
	}
	return (true);
}

/*retourne la longueur de la variable d'env*/
int	dol_c(char *token, t_dollar *dol)
{
	int		counter;
	char	*str;
	int		i;

	i = 0;
	while (token && token[i])
	{
		if (ft_strchr("$", token[i]))
		{
			str = ms_get_dolenv(token, i);
			if (!str)
				dol->count++;
			else
			{
				counter = 0;
				while (str[counter++])
					dol->count++;
			}
			if (str)
				free(str);
		}
		i++;
	}
	return (dol->count + i);
}

/*vérifie si la string contient un dollar sign*/
bool	is_dolsign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("$", str[i]))
			return (true);
		i++;
	}
	return (false);
}

/*vérifie s'il s'agit d'un signe dollar seul
retroune vrai si oui, sinon retourne faux*/
bool	dol_solo(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 1 && str[0] == '$')
		return (true);
	return (false);
}

void	ms_init_dol_struct(t_dollar *dol)
{
	dol->d_quote = 0;
	dol->s_quote = 0;
	dol->index = 0;
	dol->count = 0;
	dol->str = NULL;
	dol->name_var = NULL;
	dol->var_env = NULL;
}
