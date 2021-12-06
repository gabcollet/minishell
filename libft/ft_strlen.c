/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:39:40 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/06 12:28:03 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* La fonction strlen() calcule la longueur de la chaîne de caractères s, sans 
compter l'octet nul « \0 » final. */
/* La fonction strlen() renvoie le nombre de caractères dans la chaîne s. */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
