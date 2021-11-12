/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/12 10:52:01 by jbadia           ###   ########.fr       */
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
		free(parser->str_line);
	free(parser);
}

void	free_job_lst(t_job *job)
{
	t_job	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (job)
	{
		temp = job->next;
		while (job->cmd[i])
		{
			free(job->cmd[i]);
			i++;
		}
		if (job->cmd)
			free(job->cmd);
		job = temp;
	}
	if (job)
		free(job);
}