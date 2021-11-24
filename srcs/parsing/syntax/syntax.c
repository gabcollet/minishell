/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:05:06 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/24 10:42:50 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax.h"

/*Passe au travers de la liste de tokens et vérifie la syntaxe
pour les pipes et le redir. Retourne vrai si la syntaxe et correcte.
Si problème de syntaxe, donne à ret_exit la valeur 258, free la liste
et retourne faux.*/
bool	valid_syntax(t_token *token)
{
	t_token	*head;

	head = token;
	if (token->type == PIPE)
	{
		pipe_first(token);
		return (false);
	}
	while (token && token->next)
	{
		if (token->type == STRING)
			token = token->next;
		else if (token->type != STRING)
		{
			if (valid_redir_r(token) || valid_redir_l(token)
				|| valid_pipe(token) || valid_here_doc(token)
				|| valid_append(token))
				token = token->next;
			else
			{
				g_msh.ret_exit = SYNTAX_ERROR;
				free_token_lst(head);
				return (false);
			}
		}
	}
	return (true);
}

/*Vérifie la syntaxe des redirections
Retournes faux:
- si après la redir ce n'est pas un type string
- si le token suivant est NULL
Sinon retourne vrai*/
bool	valid_redir_l(t_token *token)
{
	if (token->type != REDIR_L)
		return (false);
	if (!token->next->next)
	{
		ft_putendl_fd(ERR_UNEX_NEWLINE, 2);
		return (false);
	}
	return (valid_redir_2(token));
}

bool	valid_redir_r(t_token *token)
{
	if (token->type != REDIR_R)
		return (false);
	if (!token->next->next)
	{
		ft_putendl_fd(ERR_UNEX_NEWLINE, 2);
		return (false);
	}
	return (valid_redir_2(token));
}

bool	valid_redir_2(t_token *token)
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

/*Vérifie la syntaxe des pipes
Retournes faux:
- si après le pipe ce n'est pas une string ou une redir
- si le token suivant est NULL
- si le token suivant le suivant est NULL sauf si le token suivant 
est une string ou une redir (ex: ls | cat)*/
bool	valid_pipe(t_token *token)
{
	if (token->type != PIPE)
		return (false);
	if (!token->next)
	{
		ft_putendl_fd(ERR_UNEX_PIPE, 2);
		return (false);
	}
	if (token->next->type == PIPE)
	{
		ft_putendl_fd(ERR_UNEX_PIPE, 2);
		return (false);
	}
	else if (token->next->type == STRING || is_redirection(token->next))
		return (true);
	else if (!token->next->next)
	{
		ft_putendl_fd(ERR_UNEX_PIPE, 2);
		return (false);
	}
	return (false);
}
