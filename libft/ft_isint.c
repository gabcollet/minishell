/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:53:33 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/15 18:04:35 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	int		i;
	long	temp;

	i = 0;
	temp = ft_atol(str);
	if (temp < INT_MIN || temp > INT_MAX)
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i++]) == 0)
			return (1);
	}
	return (0);
}
