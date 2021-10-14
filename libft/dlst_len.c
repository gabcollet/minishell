/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:27:39 by gcollet           #+#    #+#             */
/*   Updated: 2021/09/13 10:28:01 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	dlst_len(t_dlist *lst)
{
	int	len;

	len = 0;
	if (lst)
	{
		len++;
		while (lst->next)
		{
			lst = lst->next;
			len++;
		}
	}
	return (len);
}
