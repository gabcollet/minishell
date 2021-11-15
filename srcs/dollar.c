#include "minishell.h"

// FIXME tester avec $USE 
/*remplace le $ENV par sa variable complète et retournes la nouvelle string*/
char		*replace_dol_w_env(char *token)
{
	char 	*var_env = NULL;
	char	*name_var = NULL;
	char	*temp = NULL;
	char	*str;
	int		i = 0;
	int		j = 0;
	int		index = 0;
	
	temp = ft_strdup(token);
	str = ft_calloc((dollar_counter(temp) + 1), sizeof(char*));
	while (temp[index])
		{
			if (ft_strchr("$", temp[index]))
			{
				name_var = get_arg(temp, index);
				if (!check_dol(name_var))
					i++;
				else
				{
					var_env = ms_get_dolenv(temp, index);
					if (!var_env)
						break ;
					j = 0;
					while (var_env[j])
						str[i++] = var_env[j++];
					free(var_env);
				}
				index += ft_strlen(name_var) + 1;
				free(name_var);
				if (ft_strchr("$", temp[index]))
					continue ;
			}
			str[i] = temp[index];
			i++;
			index++;
		}
		 free(temp);
		return(str);
}
/*va chercher la variable dans env et retourne ce qu'il y a après le = */
char	*ms_get_dolenv(char *tab, int i)
{
	char *str;
	char *arg;
	char *temp;

	arg = get_arg(tab, i);
	if (!check_dol(arg))
		return (NULL);
	str = ms_get_varenv(g_msh.env, arg);
	if (!str)
		return (NULL);
	temp = ft_substr(str, 0, ft_strlen(str));
	free(arg);
	free(str);
	return (temp);
}

/*va chercher et retroune le nom de la variable quit suit le signe $ dans une string*/
char *get_arg(char *tab, int i)
{
	int	k;
	char *arg;
	int	is_dol;

	k = 0;
	is_dol = 0;
	arg = ft_calloc(100, sizeof(char *));
	while (tab[i] && is_dol < 1)
	{
		if (ft_strchr("$", tab[i]))
		{
			while (!ft_strchr(WHITESPACE, tab[i]) && !ft_strchr(WHITESPACE, tab[i + 1]) 
			&& !ft_strchr("$", tab[i + 1]) && !is_quote(tab, i + 1) && !ft_strchr("/", tab[i + 1]))
			{
				arg[k] = tab[i + 1];
				i++;
				k++;
			}
			is_dol = 1;
		}
		i++;
	}
	return(arg);
}

/*vérifie sur la string qui suit $ est valide: 
ne commence pas par un chiffre et ne contient que des caractères alphanum ou _*/
bool	check_dol(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[0]))
			return (false);
		if (ft_strchr("_", tab[i]) || ft_strchr("\'", tab[i]) || ft_strchr("\"", tab[i]))
			i++;
		if (!ft_isalnum(tab[i]))
			return (false);
		i++;
	}
	return (true);
}

/*retourne la longueur de la variable d'env*/
int	dollar_counter(char *token) //FIXME : invalid read of size 1
{
	int	counter;
	char	*str;
	int		i;

	i = 0;
	counter = 0;
	while (token && token[i])
	{
		if (ft_strchr("$", token[i]))
		{
			str = ms_get_dolenv(token, i);
			if (!str)
				return (1);
			while (str[counter])
				counter++;
			if (str)
				free(str);
		}
		i++;
	}
	return (counter + i);
}

/*vérifie si la string contient un dollar sign*/
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