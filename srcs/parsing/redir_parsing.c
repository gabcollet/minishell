/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:45:11 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/10 15:28:59 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tout ca est bon pour les vidanges */

/* void	init_redir(void)
{
	g_msh.redir_input = NULL;
	g_msh.redir_output = NULL;
	g_msh.append_output = NULL;
	g_msh.here_doc = NULL;
}

void	set_redir_info(int g_redir, char *string, int i, int file_len)
{
	if (g_redir == 1)
		g_msh.redir_output = ft_substr(string, i, file_len);
	else if (g_redir == 2)
		g_msh.append_output = ft_substr(string, i, file_len);
	else if (g_redir == 3)
		g_msh.redir_input = ft_substr(string, i, file_len);
	else if (g_redir == 4)
		g_msh.here_doc = ft_substr(string, i, file_len);
}

int	get_redir_info(char *string, int g_redir, int i)
{
	int	file_len;

	file_len = 0;
	while (string[i] == ' ')
		i++;
	if (string[i] == '\0')
	{
		printf("minishell: parse error near \'\\n\'\n");
		return (1);
	}
	while (string[i + file_len] != ' ')
		file_len++;
	set_redir_info(g_redir, string, i, file_len);
	while (string[i + file_len + 1] == ' ')
		file_len++;
	if (string[-1] != ' ')
		file_len--;
	i = ft_strcpy(string, &string[i + file_len + 1]);
	string[i] = '\0';
	return (0);
}

int	parse_redir(char *arg)
{
	char	*string;
	int		i;

	i = 0;
	init_redir();
	string = ft_strchr(arg, '>');
	if (string != NULL)
	{
		if (string[1] == '>' && get_redir_info(string, 2, 2) == 1)
			i = 1;
		else if (get_redir_info(string, 1, 1) == 1)
			i = 1;
	}
	string = ft_strchr(arg, '<');
	if (string != NULL)
	{
		if (string[1] == '<' && get_redir_info(string, 4, 2) == 1)
			i = 1;
		else if (get_redir_info(string, 3, 1) == 1)
			i = 1;
	}
	if (i == 1)
		return (1);
	return (0);
} */
