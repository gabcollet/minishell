/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:34:34 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/23 20:41:52 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_msh g_msh;

/* Effectue le builtin-cd */
int	ms_cd(char *arg)
{
	char	c[PATH_MAX];

	if (arg == NULL)
	{
		arg = ms_get_env(g_msh.env, "HOME=") + 5;
		if ((arg - 5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (-1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		printf("cd: %s: No such file or directory\n", arg);
		return (-1);
	}
	ms_set_env(g_msh.env, ft_strjoin("OLDPWD=", c));
	getcwd(c, sizeof(c));
	ms_set_env(g_msh.env, ft_strjoin("PWD=", c));
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	char	c[PATH_MAX];
// 	int i = 0;
// 	ac = 0;
//	
// 	/* -----------malloc la global */
// 	ms_dup_env(env);
// 	/* -----------print l'env avant d'etre modifier */
// 	i = 0;
// 	while (g_msh.env[i])
// 		printf("%s\n", g_msh.env[i++]);
// 	printf("----------------------------------------\n");
// 	i = ms_cd(av[1]);
// 	/* -----------check le retour et le pwd */
// 	getcwd(c, sizeof(c));
// 	printf("%d\n", i);
// 	printf("%s\n", c);
// 	/* -----------print l'env apres la modif */
// 	i = 0;
// 	while (g_msh.env[i])
// 		printf("%s\n", g_msh.env[i++]);
// 	/* -----------free l'env */
// 	ft_free_tab(g_msh.env);
// }