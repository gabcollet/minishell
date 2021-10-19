/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:34:34 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/19 17:28:10 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **g_env;

char	*ms_get_env(char *arg)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(arg);
	while (ft_strnstr(g_env[i], arg, len) == 0 && g_env[i])
			i++;
	if (g_env[i] == NULL)
		return (NULL);
	return (g_env[i]);
}

/* void set_env(const char* arg, const char* value)
{
	-fouiller dans env pour trouver arg=
	-si tu trouve tu free la ligne dans env
	-strdup la new value dedant
	-si cest une new value pas trouver
	-copie tout le env dans un nouveau tab avec un espace de plus
	-ajopute la new valeur a la fin de la new tab
	-free lancienne tab
} */

int ms_cd(char *arg)
{
	char	c[PATH_MAX];
	int		i;
	
	//si on fait seulement cd sans arg, ca retourne au home
	if (arg == NULL)
		arg = ms_get_env("HOME=") + 5;
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
		return (-1);
	i = 0;
	//pour les deux whiles ca va devoir passer par set_env pour pas leaks
	while (ft_strnstr(g_env[i], "OLDPWD=", 7) == 0)
		i++;
	g_env[i] = ft_strjoin("OLDPWD=", c);
	i = 0;
	while (ft_strnstr(g_env[i], "PWD=", 4) == 0)
		i++;
	getcwd(c, sizeof(c));
	g_env[i] = ft_strjoin("PWD=", c);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char	c[PATH_MAX];
	int i = 0;
	
	g_env = env;
	/* while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	i = 0;
	printf("----------------------------------------\n"); */
	i = ms_cd(av[1]);
	
	getcwd(c, sizeof(c));
	printf("%d\n", i);
	printf("%s\n", c);
	/* while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	} */
}
