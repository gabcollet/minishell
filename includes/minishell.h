/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/10/19 17:18:18 by gcollet          ###   ########.fr       */
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

int		ms_echo(char **arg);
char	*ms_get_env(char *arg);
int		ms_cd(char *arg);

typedef struct s_msh
{
	char **env;
	int	ret_exit;
}				t_msh;

t_msh g_msh;

void	print_tab(char **tab);

//env
char 	*ms_get_path(void);
char 	**ms_dup_arr(char **arr);
size_t	ms_line_counter(char **env);

//free_func
void	ft_free_tab(char **tab);
void	ft_free_struct(t_msh *g_msh);
#endif