#include "minishell.h"

bool	dol_solo(char *str);

/*remplace le $ENV par sa variable complète et retournes la nouvelle string*/
char		*replace_dol_w_env(char *token)
{
	char 	*var_env = NULL;
	char	*name_var = NULL;
	char	*temp = NULL;
	char	*str; //peut etre mettre str dans ma struct 
	int		i = 0;
	int		j;
	int k = 0;
	int		index = 0;
	int		s_quote = 0;
	int d_quote = 0;
	
	temp = ft_strdup(token);
	str = ft_calloc((dollar_counter(temp) + 1 +ft_strlen(token)), sizeof(char*));
	while (temp[index])
		{
			if (temp[index] == '\'' && d_quote == 0) // faire une fonction qui regarde ca
			{
				s_quote++;
				if (s_quote == 2)
					s_quote = 0;
			}
			else if (temp[index] == '\"' && s_quote == 0)
			{
				d_quote++;
				if (d_quote == 2)
					d_quote = 0;
			}
			else if (ft_strchr("$", temp[index]) && s_quote == 0) 
			{
				name_var = get_arg(temp, index);
				if (!check_dol(name_var))
				{
					if (dol_solo(name_var))
					{
						j = 0;
						index--;
					}
					else
						j = 1; //si je le met à 0 et que je fais j++ dans le while mais ++j en dessous ?
					while (name_var[k++])
						str[i++] = name_var[j++];
					k = 0;
					//i--; // si j'enlève le ++ je peux peut etre retirer le --
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
				continue ;
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
				is_dol = 1; //ca marche pas
			}
			if (is_dol == 0)
			{
				arg[0] = tab[i];
				return (arg);
			}
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

/*vérifie s'il s'agit d'un signe dollar seul
retroune vrai si oui, sinon retourne faux*/
bool	dol_solo(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i > 2)
		return (false);
	return (true);
}