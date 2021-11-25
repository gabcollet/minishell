/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:42:01 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/25 16:17:29 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* imprime l'environnement */
int	ms_env(void)
{
	int	i;

	i = 0;
	while (g_msh.env[i])
		printf("%s\n", g_msh.env[i++]);
	return (0);
}
