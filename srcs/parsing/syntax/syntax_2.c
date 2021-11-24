/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:16:55 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/24 10:43:15 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

bool	valid_here_doc(t_token	*token)
{
	if (token->type != HERE_DOC_L)
		return (false);
	if (!token->next->next)
	{
		ft_putendl_fd(ERR_UNEX_NEWLINE, 2);
		return (false);
	}
	return (valid_append_2(token));
}

bool	valid_append(t_token *token)
{
	if (token->type != APPEND)
		return (false);
	if (!token->next->next)
	{
		ft_putendl_fd(ERR_UNEX_NEWLINE, 2);
		return (false);
	}
	return (valid_append_2(token));
}

bool	valid_append_2(t_token *token)
{
	if (token->next->type != STRING)
	{
		if (token->next->type == REDIR_R)
			ft_putendl_fd(ERR_UNEX_REDIR_R, 2);
		else if (token->next->type == REDIR_L)
			ft_putendl_fd(ERR_UNEX_REDIR_L, 2);
		else if (token->next->type == PIPE)
			ft_putendl_fd(ERR_UNEX_PIPE, 2);
		else if (token->next->type == HERE_DOC_L)
			ft_putendl_fd(ERR_UNEX_HEREDOC_L, 2);
		else if (token->next->type == APPEND)
			ft_putendl_fd(ERR_UNEX_APPEND, 2);
		else if (token->next->type == PIPE
			&& token->next->next->type == PIPE)
			ft_putendl_fd(ERR_UNEX_PIPES, 2);
		else if (token->next->type == REDIR_L
			&& token->next->next->type == REDIR_R)
			ft_putendl_fd(ERR_UNEX_REDIRS_LR, 2);
		return (false);
	}
	return (true);
}

void	pipe_first(t_token *token)
{
	g_msh.ret_exit = SYNTAX_ERROR;
	ft_putendl_fd(ERR_UNEX_PIPE, 2);
	free_token_lst(token);
}