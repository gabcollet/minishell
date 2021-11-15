/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:19:58 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/15 18:22:54 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exit [n]
-provoque l'arrêt du programme shell avec un code de retour ($?) égal à n.
-Si n n'est pas précisé, le code de retour fourni est celui de la dernière 
commande exécutée.
-exit prend seulement des arguments de type entier compris entre 0 et 255
*/

int	ft_isllong(char *str)
{
	int		i;
	long	temp;

	i = 0;
	if (str[0] == '-' && ft_strlen(str) >= 20
		&& ft_strcmp(&str[1], "9223372036854775808") > 0)
		return (1);
	else if (ft_strlen(str) >= 19
		&& ft_strcmp(str, "9223372036854775807") > 0)
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i++]) == 0)
			return (1);
	}
	return (0);
}

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
