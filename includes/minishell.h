/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/22 09:42:22 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define WHITESPACE "\t\n\v\f\r "
#define REDIRECTION "|<>"

typedef struct s_msh
{
	char	**env;
	int		ret_exit;
	
}				t_msh;

typedef enum	e_type
{
	VOID,
	PIPE,
	STRING,
	SPACE,
	REDIR_L,
	REDIR_R,
	HERE_DOC_L,
	HERE_DOC_R, 
}				t_type;

typedef enum	e_state
{
	TEXT,
	S_QUOTE,
	D_QUOTE,
}				t_state;

typedef struct s_token
{
	struct	s_token	*previous;
	t_type	type;
	char	*str_tok;
	struct s_token *next;
}				t_token;

typedef	struct s_parser
{
	char	*str_line;
	size_t		index;
	t_state state;
}				t_parser;


t_msh g_msh;

void	print_tab(char **tab);

//env
char 	*ms_get_path(void);
void	ms_get_env(char **env);
char 	**ms_dup_arr(char **arr);
size_t	ms_line_counter(char **env);

//free_func
void	ft_free_tab(char **tab);

//token/parse
void	ms_init_s_token(t_token *token);
void	ms_init_s_parser(t_parser *parser);
void	ms_parsing(char *line, t_parser *parser, t_token *token);

//token_lst_utils
t_token *ms_addnew_token(t_token *tok, char *temp);
void	ms_token_addback(t_token **token, t_token *new_tok);
t_token	*ms_token_last(t_token	*token);
t_token	*ms_token_new(void	*token);
void	ms_add_tok_to_list(t_token *tok, char *temp);
bool empty_str(char *str);
void printList(t_token *tok);
#endif