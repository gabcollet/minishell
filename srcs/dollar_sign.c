#include "minishell.h"

void	replace_dol_w_env(char **tab, t_job *job, int k)
{
	char *str;
	char **str2;
	char *arg;
	char *temp;
	int	i;

	arg = get_arg(tab);
	str = ms_get_env(g_msh.env, arg);
	str2 = (char**)ft_calloc(ft_strlen(str) + ft_strlen(*tab), sizeof(char*));
	temp = ft_substr(str, ft_strlen(arg) + 1, ft_strlen(str) - ft_strlen(arg));
	i = 0;
	while (tab[i])
	{
		if ((ft_strchr("$", *tab[i])))
		{
			job->cmd[k] = temp;
			//free(temp);
		}
		// else
		// 	str2[i] = tab[i];
		i++;
	}
}


char *get_arg(char **tab)
{
	int	i;
	int j;
	char *arg;

	i = 0;
	j = 0;
	arg = ft_calloc(10, sizeof(char *));
	if (ft_strchr("$", *tab[i]))
	{
		while (!ft_strchr(WHITESPACE, tab[i][j]))
		{
			arg[j] = tab[i][j + 1];
			j++;
		}	
	}	
	return(arg);
}