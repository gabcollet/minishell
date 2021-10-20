# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 19:56:08 by gcollet           #+#    #+#              #
#    Updated: 2021/10/20 10:11:45 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG	= minishell

SRCS 	= srcs/main.c srcs/env.c srcs/free_func.c srcs/ms_echo.c

OBJS 	= $(patsubst $(SRCPATH)/%.c,$(OBJPATH)/%.o,$(SRCS))
SRCPATH = srcs
OBJPATH = obj

HEADER	= -Iincludes -Ilibft

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

${OBJPATH}/%.o: ${SRCPATH}/%.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $@

all:	build-repo ${PROG}

${PROG}:	${OBJS}
					@make re -C ./libft
					@$(CC) ${OBJS} -L libft -l ft -o ${PROG} -lreadline 
					@echo "\n\033[32m\033[1mMinishell ALPHA v-1.0 Compiled!\n\033[0m"

clean:
					@make clean -C ./libft
					@rm -rf ${OBJPATH}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f ${PROG}

re:			fclean all

build-repo:
			@mkdir -p $(OBJPATH);

.PHONY: all clean fclean re bonus