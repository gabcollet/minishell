/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:48:56 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/19 14:43:45 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Retournes vrai si le token est de type redirection, sinon faux*/
bool	is_redirection(t_token *token)
{
	if (token->type == REDIR_L || token->type == REDIR_R
		|| token->type == HERE_DOC_L || token->type == APPEND)
		return (true);
	return (false);
}

/*Rassemble les tokens pour créer des "jobs" en fonction des pipes*/
t_job	*ms_job(t_job *job, t_token *token)
{	
	job = ms_job_newlst();
	while (token && token->str_tok)
	{
		if (token->type == PIPE)
		{
			ms_job_addback(&job, ms_job_newlst());
			job = job->next;
		}
		else if (token->type == STRING)
			token_to_tab(token, job);
		else if (is_redirection(token))
		{
			job = redirection_to_tab(token, job);
			token = token->next;
		}
		token = token->next;
	}
	ms_head_list_job(job);
	return (job);
}

/*Enregistre les redirections et leur fichier 
depuis la struct token vers la struct job*/
t_job	*redirection_to_tab(t_token *token, t_job *job)
{
	int	counter;
	int	i;

	if (!job->file)
	{
		counter = redir_counter(token);
		job->file = ft_calloc((counter * 2) + 2, sizeof(char *));
	}
	i = 0;
	while (job->file[i])
		i++;
	job->file[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char));
	ft_strcpy(job->file[i], token->str_tok);
	i++;
	if (!token->next)
		return (job);
	token = token->next;
	job->file[i] = ft_calloc(ft_strlen(token->str_tok) + 1, sizeof(char));
	ft_strcpy(job->file[i], token->str_tok);
	return (job);
}

/*Compte et retourne le nombre de redirection contenue dans l'input*/
int	redir_counter(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		if (tok->type == STRING)
			tok = tok->next;
		if (is_redirection(tok))
			i++;
		tok = tok->next;
	}
	return (i);
}
