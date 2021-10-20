/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/20 15:14:52 by gcollet          ###   ########.fr       */
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

typedef struct s_msh
{
	char **env;
	int	ret_exit;
}				t_msh;

t_msh g_msh;

//ms_cd.c
int		ms_cd(char *arg);

//ms_echo.c
int		ms_newline(char *arg);
int		ms_echo(char **arg);

//utils.c
char	**ms_matrix_add_line(char **matrix);

//env.c
char 	*ms_get_path(void);
char 	**ms_dup_arr(char **arr);
char	*ms_get_env(char *arg);
void	set_env(const char *arg, const char *new_content);
size_t	ms_line_counter(char **env);

//free_func.c
void	ft_free_tab(char **tab);
void	ft_free_struct(t_msh *g_msh);

//main.c
void	init_shell();
void	print_tab(char **tab);
int		main(int argc, char *argv[], char **env);

#endif