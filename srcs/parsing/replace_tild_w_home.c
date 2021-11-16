#include "minishell.h"


t_token	*ms_expand_tild(t_token *token)
{
	char	*temp;
	t_token	*head;

	head = token;
	temp = NULL;
	while (token && token->str_tok)
	{
		temp = ft_strdup(token->str_tok);
		free(token->str_tok);
		token->str_tok = replace_tild_w_home(temp);
		token = token->next;
		free(temp);
	}
	return(head);
}

char	*replace_tild_w_home(char *token)
{
	char	*temp;
	int		index;
	char	*home;
	int		i;
	int		j;


	index = 0;
	i = 0;
	home = ms_get_varenv(g_msh.env, "HOME");
	temp = ft_calloc(tild_counter(token) * ft_strlen(home) + 1, sizeof(char));
	while (token[index])
	{
		j = 0;
		if (token[index] == '~')
		{
			while (home[j])
				temp[i++] = home[j++];
			index ++;
		}
		temp[i++] = token[index++];
	}
	return (temp);
}

int	tild_counter(char *str)
{
	int	i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if(str[i] == '~')
			counter++;
		i++;
	}
	return(counter + i);
}