#include "minishell.h"

/*
char	*ms_get_dolenv(char **tab)
{
	char *str;
	char *arg;
	char *temp;

	arg = get_arg(tab);
	str = ms_get_env(g_msh.env, arg);
	temp = ft_substr(str, ft_strlen(arg) + 1, ft_strlen(str) - ft_strlen(arg));
	return (temp);
}
void	replace_dol_w_env(char **tab, t_job *job, int k)
{
	char *arg;
	char *var_env;
	char *temp1;
	int	i;
	int j = 0;
	int	index = 0;
	int	test = 0;

	var_env = get_arg(tab);
	arg = ms_get_dolenv(tab);
	temp1 = ft_substr(job->cmd[k], 0, ft_strlen(job->cmd[k]));
	free(job->cmd[k]);
	job->cmd[k] = ft_calloc(ft_strlen(arg) + ft_strlen(temp1) + 1, sizeof(char*));
	i = 0;
	while (temp1[test])
	{
		if ((ft_strchr("$", temp1[i])))
		{
			while (arg[j])
			{
				job->cmd[k][i] = arg[j];
				j++;
				i++;
			}
		index += ft_strlen(var_env) + 1;
		}
		job->cmd[k][i] = temp1[index];
		i++;
		index++;
		test++;
	}
	free(arg);
}

char *get_arg(char **tab)
{
	int	i;
	int j;
	int	k;
	char *arg;

	i = 0;
	k = 0;
	arg = ft_calloc(10, sizeof(char *));
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_strchr("$", tab[i][j]))
			{
				while (!ft_strchr(WHITESPACE, tab[i][j]) && !ft_strchr(WHITESPACE, tab[i][j +1]))
				{
					arg[k] = tab[i][j + 1];
					j++;
					k++;
				}
				if(arg)
					return (arg);
			}
			j++;
		}	
	i++;
	}
	return(arg);
}*/

bool	is_dolsign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("$", str[i]))
			return (true);
		i++;
	}
	return (false);
}