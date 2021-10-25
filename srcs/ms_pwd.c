/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:30:22 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/22 12:05:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	c[PATH_MAX];

	if (getcwd(c, sizeof(c)) == NULL)
		return (-1);
	printf("%s\n", c);
	return (0);
}

// int main()
// {
// 	ms_pwd();
// }