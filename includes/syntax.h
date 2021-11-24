/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:52:32 by jbadia            #+#    #+#             */
/*   Updated: 2021/11/24 10:43:11 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "minishell.h"

# define ERR_QUOTE_S "minishell : invalid single quote"
# define ERR_QUOTE_D "minishell : invalid double quote"
# define ERR_UNEX_PIPES "minishell : syntax error near unexpected token '||'"
# define ERR_UNEX_PIPE "minishell : syntax error near unexpected token '|'"
# define ERR_UNEX_REDIR_L "minishell : syntax error near unexpected token '<'"
# define ERR_UNEX_REDIR_R "minishell : syntax error near unexpected token '>'"
# define ERR_UNEX_HEREDOC_L "minishell : syntax error near\
 unexpected token '<<'"
# define ERR_UNEX_APPEND "minishell : syntax error near\
 unexpected token '>>'"
# define ERR_UNEX_REDIRS_LR "minishell : syntax error near\
 unexpected token '<>'"
# define ERR_UNEX_NEWLINE "minishell : syntax error near\
 unexpected token 'newline'"
# define SYNTAX_ERROR 258

//error.c
void	ms_error_quote(t_parser *parser);
bool	is_only_space(char *str);

//syntax.c
bool	valid_syntax(t_token *token);
bool	valid_redir_l(t_token *token);
bool	valid_redir_r(t_token *token);
bool	valid_redir_2(t_token *token);
bool	valid_pipe(t_token *token);

//syntax_2.c
bool	valid_here_doc(t_token	*token);
bool	valid_append(t_token *token);
bool	valid_append_2(t_token *token);
void 	pipe_first(t_token *token);

#endif