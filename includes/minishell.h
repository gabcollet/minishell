/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/19 19:07:23 by jbadia           ###   ########.fr       */
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

enum	e_type
{
	PIPE;
	TEXT;
	SPACE;
	REDIR_L;
	REDIR_R;
	HERE_DOC_L;
	HERE_DOC_R; 
}		t_type;

enum	e_state
{
	TEXT;
	S_QUOTE;
	D_QUOTE;
}		t_state;

typedef struct s_token
{
	struct	s_token	*previous;
	t_type	type;
	char	*token;
	struct s_token *next;
}				t_token;

typedef	struct s_parser
{
	char	*str_line;
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

#endif