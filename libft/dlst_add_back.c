/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:29:30 by gcollet           #+#    #+#             */
/*   Updated: 2021/09/13 10:29:47 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dlst_add_back(t_dlist **head, t_dlist *new)
{
	t_dlist	*temp;

	if (*head == NULL)
	{
		temp = *head;
		*head = new;
		free(temp);
	}
	else
	{
		temp = dlst_last(*head);
		temp->next = new;
		new->prev = temp;
	}
}
