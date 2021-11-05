/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:31:38 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/02 13:49:33 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strcpy() function copies all the characters from the 
NUL-terminated string src to dst, NUL-terminating the result. */
/* The strcpy() functions return the total length of the string 
they tried to create. For strcpy() that means the length of src. */

#include "libft.h"

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
