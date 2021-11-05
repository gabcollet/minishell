#include "minishell.h"

void	replace_dol_w_env(char **tab, t_job *job, int k)
{
	char *str;
	char *arg;
	char *temp;
	int	i;

	arg = get_arg(tab);
	str = ms_get_env(g_msh.env, arg);
	temp = ft_substr(str, ft_strlen(arg) + 1, ft_strlen(str) - ft_strlen(arg));
	free(job->cmd[k]);
	job->cmd[k] = ft_calloc(ft_strlen(temp) +1, sizeof(char*));
	i = 0;
	if ((ft_strchr("$", *tab[i])))
		ft_strlcpy(job->cmd[k], temp, ft_strlen(temp) + 1);
	free(arg);
	free(temp);
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