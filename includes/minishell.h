/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/28 16:14:15 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
/* include pour linux */
/* # include <linux/limits.h> */


#define WHITESPACE "\t\n\v\f\r "
#define REDIRECTION "|<>"
#define ERR_QUOTE_S "invalid single quote"
#define ERR_QUOTE_D "invalid double quote"

typedef struct s_msh
{
	char	**env;
	char	**env_export;
	int		ret_exit;
}				t_msh;

typedef enum	e_type
{
	VOID,
	PIPE,
	STRING,
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

//ms_cd.c
int		ms_cd(char *arg);

//ms_echo.c
int		ms_newline(char *arg);
int		ms_echo(char **arg);

//utils.c
char	**ms_matrix_add_line(char **matrix, char *new_line);

//ms_export.c
int		ms_export(char **arg);
int		ms_check_export_arg(char *arg);
char	*ms_make_string(char *arg);
void	ms_export_valid_arg(char *arg, char *strings);
void	ms_export_sort(void);
void	ms_init_export(void); /* a mettre dans le init */

//env.c
char 	*ms_get_path(void);
void	ms_dup_env(char **env);
char	*ms_get_env(char **env, char *arg);
void	ms_set_env(char **env, char *value);
size_t	ms_line_counter(char **env);

//free_func.c
void	ft_free_tab(char **tab);
void	free_token_lst(t_token *tok);
void	free_struct(t_parser *parser);
void	free_all(char *line, char **path);

//parser
char	*ms_init_s_parser(t_parser *parser, char *line);
void ms_parsing(char *line);
bool empty_str(char *str);
void printList(t_token *tok);
char *ms_trim_space(char *str);

//token_lst_utils
t_token	*ms_token_last(t_token	*token);
t_token	*ms_token_newlst(void	*token);
void	ms_token_addback(t_token **token, t_token *new_tok);


//token_utils
bool ms_get_token(t_parser *parser, t_token *token);
char *ms_get_next_tok(t_parser *parser, char *temp);
t_token	*ms_add_tok_to_lst(t_parser *parser, t_token *token);
void	ft_free_struct(t_msh *g_msh);

//parser_utils
bool	tokenize_redir(t_parser *parser, t_token *token);
int ms_find_close_quote(t_parser *parser, char quote);
void	change_state(t_parser *parser);
int	ms_handle_quote(t_parser *parser);
bool tokenize_string(t_token *token);

//error
void	ms_error_quote(t_parser *parser);

//syntax
void ms_check_syntax(t_token *token);
char *ms_remove_quote(char *str);

//main.c
void	init_shell();
void	print_tab(char **tab);
/* int		main(int argc, char *argv[], char **env); */

#endif