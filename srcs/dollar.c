#include "minishell.h"

char	*ms_get_dolenv(char *tab);
char *get_arg(char *tab);

int	dol_counter(t_token *token)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (token->str_tok[i])
	{
		if (ft_strchr("$", token->str_tok[i]) && token->type == TEXT)
			counter++;
		i++;
	}
	return (counter);
}

void	replace_dol_w_env(char *tab, t_token *token)
{
	char 	*var_env;
	char	*name_var;
	char	*temp;
	int		i = 0;
	int		j = 0;
	int		index = 0;

	name_var = get_arg(tab);
	var_env = ms_get_dolenv(tab);
	temp = ft_strdup(token->str_tok);
	free(token->str_tok);
	token->str_tok = ft_calloc(ft_strlen(temp) + ft_strlen(var_env) + 1, sizeof(char*));
		while (temp[index])
		{
			if (ft_strchr("$", temp[index]))
			{
				while (var_env[j])
					token->str_tok[i++] = var_env[j++];
				index += ft_strlen(name_var) + 1;
			}
			token->str_tok[i] = temp[index];
			i++;
			index++;
		}
}

char	*ms_get_dolenv(char *tab)
{
	char *str;
	char *arg;
	char *temp;

	arg = get_arg(tab);
	str = ms_get_env(g_msh.env, arg);
	temp = ft_substr(str, ft_strlen(arg) + 1, ft_strlen(str) - ft_strlen(arg));
	return (temp);
}

char *get_arg(char *tab)
{
	int	i;

	int	k;
	char *arg;
	char *temp;

	i = 0;
	k = 0;
	arg = ft_calloc(10, sizeof(char *));
	while (tab[i])
	{
		if (ft_strchr("$", tab[i]))
		{
			while (!ft_strchr(WHITESPACE, tab[i]) && !ft_strchr(WHITESPACE, tab[i +1]))
			{
				arg[k] = tab[i + 1];
				i++;
				k++;
			}
				// if(arg)
				// 	return (arg);
		}
		i++;
	}
	//trimmer tous les types de quote
	temp = ft_strtrim(arg, "\'");
	free(arg);
	return(temp);
}
