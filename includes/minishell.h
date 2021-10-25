/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/25 11:33:01 by gcollet          ###   ########.fr       */
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


typedef struct s_msh
{
	char	**env;
	char	**env_export;
	int		ret_exit;
}				t_msh;

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
void	ft_free_struct(t_msh *g_msh);

//main.c
void	init_shell();
void	print_tab(char **tab);
/* int		main(int argc, char *argv[], char **env); */

#endif