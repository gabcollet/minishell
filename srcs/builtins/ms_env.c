/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:42:01 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/25 16:47:31 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(void)
{
	int	i;

	i = 0;
	while (g_msh.env[i])
		printf("declare -x %s\n", g_msh.env[i++]);
}