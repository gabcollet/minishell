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
	int k = 0;
	int		index = 0;
	int		d_quote_count = 0;
	
	temp = ft_strdup(token);
	str = ft_calloc((dollar_counter(temp) + 1 +ft_strlen(token)), sizeof(char*));
	while (temp[index])
		{
			j = 0;
			if (ft_strchr("$", temp[index]))
			{
				name_var = get_arg(temp, index);
				if (!check_dol(name_var))
				{
					j = 1;
					while (name_var[k++])
							str[i++] = name_var[j++];
					i--;
				}
				else
				{
					var_env = ms_get_dolenv(temp, index);
					if (var_env)
					{
						j = 0;
						while (var_env[j])
							str[i++] = var_env[j++];
					}
					free(var_env);
				}
				index += ft_strlen(name_var) + 1;
				free(name_var);
				if (ft_strchr("$", temp[index]))
					continue ;
			}
			if (temp[index] == '\"')
			{
				d_quote_count++;
			}
			if ((temp[index] == '\'' && (d_quote_count % 2 == 0)) || (temp[index] == '\'' && d_quote_count == 1))
			{
				while(temp[index++] != '\'')
					str[i++] = temp[index++];
			}
			str[i++] = temp[index++];
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
	if( arg[i] == '?')
	{
		temp = ft_itoa(g_msh.ret_exit);
		return (temp);
	}
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
			while ((!ft_strchr(WHITESPACE, tab[i]) && !ft_strchr(WHITESPACE, tab[i + 1]) 
			&& !ft_strchr("$", tab[i + 1]) && !is_quote(tab, i + 1) && !ft_strchr("/", tab[i + 1]) 
			&& ft_isalnum(tab[i + 1])) || (tab[i + 1] == '?'))
			{
				arg[k] = tab[i + 1];
				i++;
				k++;
				if (tab[i - 1] == '$' && arg[k - 1] == '?')
					return(arg);
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
		else if (ft_strchr("_", tab[i]) || ft_strchr("\'", tab[i]) || ft_strchr("\"", tab[i]) 
				|| ft_isdigit(tab[i]) || ft_strchr("?", tab[i]))
			i++;
		else if (!ft_isalnum(tab[i]))
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

t_token	*expand_dol_sign(t_token *token)
{
	char	*temp;
	t_token	*head;

	head = token;
	temp = NULL;
	while (token && token->str_tok)
	{
		temp = ft_strdup(token->str_tok);
		free(token->str_tok);
		token->str_tok = replace_dol_w_env(temp);
		token = token->next;
		free(temp);
	}
	return(head);
}
