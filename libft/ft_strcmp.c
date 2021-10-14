/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 09:59:15 by gcollet           #+#    #+#             */
/*   Updated: 2021/08/20 10:00:46 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* La fonction strcmp() compare les deux chaînes s1 et s2. Elle renvoie un 
entier négatif, nul, ou positif, si s1 est respectivement inférieure, égale 
ou supérieure à s2. */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
