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