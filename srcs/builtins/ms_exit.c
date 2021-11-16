/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:19:58 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/16 16:11:28 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exit [n]
-provoque l'arrêt du programme shell avec un code de retour ($?) égal à n.
-Si n n'est pas précisé, le code de retour fourni est celui de la dernière 
commande exécutée.
-exit prend seulement des arguments de type entier compris entre 0 et 255
*/
int	ms_check_exit_arg(char *arg)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", arg);
		g_msh.ret_exit = 255;
		return (1);
	}
	exit_code = ft_atoll(arg);
	g_msh.ret_exit = exit_code % 256;
	if (g_msh.ret_exit < 0 || g_msh.ret_exit > 255)
		g_msh.ret_exit = 255;
	return (0);
}

void	ms_exit(char **arg)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (arg[0])
	{
		i = ms_check_exit_arg(arg[0]);
		if (arg[1] && i == 0)
		{
			printf("minishell: exit: too many arguments\n");
			g_msh.ret_exit = 1;
			return ;
		}
	}
	exit(g_msh.ret_exit);
}
