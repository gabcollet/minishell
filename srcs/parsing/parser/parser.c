/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:55:40 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/29 13:16:52 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

/*Compte le nombre de type string présente dans la struct et le retourne*/
int	counter_string(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else if (tok->type == REDIR_L || tok->type == REDIR_R
			|| tok->type == HERE_DOC_L || tok->type == APPEND)
			tok = tok->next;
		else if (tok->type == STRING)
			i++;
		tok = tok->next;
	}
	return (i);
}

/*Enregistre les token type string dans une job*/
void	token_to_tab(t_token *token, t_job *job)
{
	int	i;
	int	counter;

	if (!job->cmd)
	{
		counter = counter_string(token);
		job->cmd = ft_calloc(counter + 1, sizeof(char *));
	}
	i = 0;
	while (job->cmd[i])
		i++;
	job->cmd[i] = ft_calloc((ft_strlen(token->str_tok) + 1), sizeof(char));
	ft_strcpy(job->cmd[i], token->str_tok);
}

/*Fonction principale qui parse l'input*/
t_job	*ms_parsing(char *line, t_job *job_first)
{
	char		*temp;
	t_token		*token;
	t_parser	*parser;

	token = ms_token_newlst(NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	temp = ms_trim_space(line);
	while (!empty_str(temp))
	{
		temp = ms_init_s_parser(parser, temp);
		if (ms_get_token(parser, token))
		{
			ms_add_tok_to_lst(parser, token);
			token = token->next;
			temp = ms_get_next_tok(parser, temp);
			continue ;
		}
		free(temp);
		return (NULL);
	}
	free(temp);
	if (!valid_syntax(ms_head_list(token)))
		return (NULL);
	token = ms_expand_tild(ms_head_list(token), parser);
	return (ms_job(job_first, ms_head_list(token)));
}

/*Vérifie si la chaine est vide*/
bool	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		return (false);
	return (true);
}

/*Trimmes les whitespace de la chaine passée en paramètre
et en retourne une nouvelle*/
char	*ms_trim_space(char *str)
{
	char	*temp;
	char	*temp1;

	temp = ft_strdup(str);
	temp1 = temp;
	temp1 = ft_strtrim(temp, WHITESPACE);
	free(temp);
	return (temp1);
}
