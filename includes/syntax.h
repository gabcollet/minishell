/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:52:32 by jbadia            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/18 16:37:08 by jbadia           ###   ########.fr       */
=======
/*   Updated: 2021/11/19 10:54:42 by gcollet          ###   ########.fr       */
>>>>>>> master
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


void	ms_error_quote(t_parser *parser);
<<<<<<< HEAD
bool 	is_only_space(char *str);
=======
bool	is_only_space(char *str);

//syntax
>>>>>>> master
bool	valid_syntax(t_token *token);
bool	valid_redir_l(t_token *token);
bool	valid_redir_r(t_token *token);
bool	valid_redir_2(t_token *token);
bool	valid_pipe(t_token *token);
bool	valid_here_doc(t_token	*token);
bool	valid_append(t_token *token);
bool	valid_append_2(t_token *token);

#endif