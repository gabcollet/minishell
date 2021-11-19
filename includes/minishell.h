/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/19 14:16:58 by jbadia           ###   ########.fr       */
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
# include <dirent.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

/* include pour linux */
/* # include <linux/limits.h> */

# define WHITESPACE "\t\n\v\f\r "
# define REDIRECTION "|<>"

typedef struct s_msh
{
	char	**env;
	char	**env_export;
	char	**tok_tab;
	int		ret_exit;
	int		switch_signal;
	int		cmd_i;
	char	*user;
}				t_msh;

typedef enum e_type
{
	VOID,
	PIPE,
	STRING,
	REDIR_L,
	REDIR_R,
	HERE_DOC_L,
	APPEND,
}				t_type;

typedef enum e_state
{
	TEXT,
	S_QUOTE,
	D_QUOTE,
	KEEP_IT,
}				t_state;

typedef struct s_token
{
	struct s_token	*previous;
	t_type			type;
	t_state			state;
	char			*str_tok;
	struct s_token	*next;
}				t_token;

typedef struct s_parser
{
	char	*str_line;
	size_t	index;
	t_state	state;
	t_state	quote_state;
}				t_parser;

t_msh	g_msh;

typedef struct s_job
{
	struct s_job	*previous;
	char			**cmd;
	char			**file;
	int				fd[2];
	pid_t			pid;
	struct s_job	*next;
}				t_job;

typedef struct s_dollar
{
	int		d_quote;
	int		s_quote;
	int		index;
	char	*str;
	char	*name_var;
	char	*var_env;
}				t_dollar;

typedef	struct s_quote
{
	char quote;
	char	*temp;
	int	i;
	int	j;
	int	check;
}				t_quote;


//ms_builtins.c
int		check_builtins(char **arg);
int		ms_builtins(char **arg, int i, t_job *job);

//ms_cd.c
void	set_pwd(char *arg, char	*c);
int		ms_cd(char *arg);

//ms_env.c
void	ms_env(void);

//ms_pwd.c
int		ms_pwd(void);

//ms_exit.c
void	ms_exit(char **arg, t_job *job);
int		ms_check_exit_arg(char *arg);

//ms_echo.c
int		ms_newline(char *arg);
int		ms_echo(char **arg);

//ms_export.c
int		ms_export(char **arg);
int		ms_check_export_arg(char *arg);
char	*ms_make_string(char *arg);
void	ms_export_valid_arg(char *arg, char *strings);
void	ms_export_sort(void);

//ms_unset.c
int		ms_check_unset_arg(char *arg);
int		ms_unset(char **arg);
char	**ms_unset_remove(char **env, char *arg);

//exec.c
void	execute(char **arg);
void	child_process(t_job *job, t_job	*first);
int		ms_exec_builtins(t_job *job);
void	ms_exec(t_job *job);

//exec_utils.c
void	error(char *arg, int i);
int		open_file(char *argv, int i);
int		find_path_env(void);
char	*find_path(char *cmd);
void	free_fd(t_job *first);

//exec_redir.c
void	check_redirection(t_job *job);
void	restore_fd(int saved_stdin, int saved_stdout);

//heredoc.c
int		check_heredoc(char **redir, int stdin_fd, t_job *job);
void	init_pipe(t_job *job);
int		make_heredocs(t_job *job);
int		redir_heredoc(char *limiter, int fd, t_job *job);
void	heredoc(char *limiter, int *fd);

//signal.c
void	ctrl_c(int var);
void	nothing(int signal);
void	stop_heredoc(int signal);
void	newline(int signal);

//redir_parsing.c
void	init_redir(void);
void	set_redir_info(int g_redir, char *string, int i, int file_len);
int		get_redir_info(char *string, int g_redir, int i);
int		parse_redir(char *arg);

//utils.c
char	**ms_matrix_add_line(char **matrix, char *new_line);
char	**ms_matrix_remove_line(char **matrix, char *line);
size_t	ms_line_counter(char **env);

//env.c
char	*ms_get_path(void);
char	*ms_get_env(char **env, char *arg);
void	ms_set_env(char **env, char *value);

//free_func.c
void	free_token_lst(t_token *tok);
void	free_struct(t_parser *parser);
void	free_job_lst(t_job *job);
void 	free_dol_struct(t_dollar *dol);
void	free_exit(t_job *job);

//parser
t_job	*ms_parsing(char *line, t_job *first_job, t_parser *parser);
bool	empty_str(char *str);
void	printList(t_token *tok);
char	*ms_trim_space(char *str);
void	token_to_tab(t_token *token, t_job *job);

//token_lst_utils
t_token	*ms_token_last(t_token	*token);
t_token	*ms_token_newlst(void	*token);
void	ms_token_addback(t_token **token, t_token *new_tok);
int		counter_string(t_token *tok);
t_token	*ms_head_list(t_token *token);

//token_utils
bool	ms_get_token(t_parser *parser, t_token *token);
char	*ms_get_next_tok(t_parser *parser, char *temp);
t_token	*ms_add_tok_to_lst(t_parser *parser, t_token *token);
bool	tokenize_string(t_token *token);
void	ft_free_struct(t_msh *g_msh);

//parser_utils
bool	tokenize_redir(t_parser *parser, t_token *token);
void	change_state(t_parser *parser, t_token *token);
void	change_state_2(t_parser *parser, t_token *token, int i);
bool	tokenize_string(t_token *token);

//ms_quote.c
int		ms_find_close_quote(t_parser *parser, char quote);
int		ms_handle_quote(t_parser *parser);
int		quote_counter(t_parser *parser, char quote);
bool	is_quote(char *tab, int i);
t_token	*ms_trim_quotes(t_token *token);

//syntax
t_token	*ms_check_quote(t_token *token);
void	ms_check_syntax(t_token *token);

//init.c
void	check_shlvl(void);
char	*ms_init_s_parser(t_parser *parser, char *line);
void	ms_init_env(char **env);
void	ms_init_export(void);
void	init_shell(void);

//main.c
//int		main(int argc, char *argv[], char **env);
void	loop(void);

//dollar_sign
char	*replace_dol_w_env(char *token, t_dollar *dol);
bool	is_dolsign(char *str);
char	*ms_get_dolenv(char *tab, int i);
char	*get_arg(char *tab, int i);
int		dollar_counter(char *token);
bool	check_dol(char *tab);
t_token	*expand_dol_sign(t_token *token);
bool	dol_solo(char *str);
bool	is_to_expend(char *tab, int i);
bool	is_dol_zero(char *tab, char *arg, int i, int is_dol);

//replace_tild_w_home
char	*replace_tild_w_home(char *token);
t_token	*ms_expand_tild(t_token *token);
int		tild_counter(char *str);

//ms_job_list
void	ms_job_addback(t_job **job, t_job *new_job);
t_job	*ms_job_last(t_job *job);
t_job	*ms_job_newlst(void);
t_job	*ms_head_list_job(t_job *job);

//ms_job
t_job	*ms_job(t_job *job, t_token *token);
bool	is_redirection(t_token *token);
t_job	*redirection_to_tab(t_token *token, t_job *job);
int		redir_counter(t_token *tok);

char	*ms_get_varenv(char **env, char *arg);

void	ms_init_dol_struct(t_dollar *dol);
void	dol_s_quote(t_dollar *dol);
void	dol_d_quote(t_dollar *dol);
int		check_name_var(t_dollar *dol, int i);
void	check_var_env(t_dollar *dol, char *temp, int i);

//ms_quote_utils
void	ms_init_quote_struct(t_quote *quote);
void	quote_updater(t_quote *quote);
void	quote_trimmer(t_quote *quote, t_token *token);


#endif
