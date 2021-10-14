/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:34:12 by gcollet           #+#    #+#             */
/*   Updated: 2021/09/13 10:34:33 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*dlst_new(int content)
{
	t_dlist	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	list->pos = 0;
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
