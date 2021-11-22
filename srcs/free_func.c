/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/22 12:09:45 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_lst(t_token *tok)
{
	t_token	*temp;

	temp = NULL;
	while (tok)
	{
		temp = tok->next;
		free(tok->str_tok);
		free(tok);
		tok = temp;
	}
	free(tok);
}

void	free_struct(t_parser *parser)
{
	if (parser)
		free(parser);
}

void	free_job_lst(t_job *job)
{
	t_job	*temp;

	temp = NULL;
	while (job)
	{
		temp = job->next;
		if (job->cmd)
			ft_free_tab(job->cmd);
		if (job->file)
			ft_free_tab(job->file);
		free(job);
		job = temp;
	}
}

void	free_dol_struct(t_dollar *dol)
{
	if (dol)
		free(dol);
}

void	free_exit(t_job *job)
{
	free (g_msh.user);
	ft_free_tab(g_msh.env);
	ft_free_tab(g_msh.env_export);
	free_job_lst(job);
	rl_clear_history();
}
