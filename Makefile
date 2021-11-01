# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 19:56:08 by gcollet           #+#    #+#              #
#    Updated: 2021/11/01 19:42:04 by jbadia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG	= minishell

OBJPATH = obj/

SRCS 	= main.c env.c free_func.c token_utils.c token_list_utils.c parser.c\
			init.c utils.c ms_env.c ms_export.c ms_cd.c ms_echo.c ms_exit.c\
			ms_pwd.c ms_unset.c ms_builtins.c exec.c exec_utils.c syntax.c error.c parser_utils.c \
			ms_quote.c dollar_sign.c

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJPATH), $(OBJFILES))
VPATH   = srcs srcs/builtins srcs/parsing

HEADER	= -Iincludes -Ilibft

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

all:	build-repo ${PROG}

${PROG}:	${OBJS}
					@make re -C ./libft
					@stty -echoctl
					@$(CC) ${OBJS} -Llibft -Llib -l ft -o ${PROG} -lreadline -lcurses
					@echo "\n\033[32m\033[1mMinishell ALPHA v-1.1 Compiled!\n\033[0m"

${OBJPATH}%.o:%.c
					@gcc ${CFLAGS} ${HEADER} -o $@ -c $<

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@rm -rf ${OBJPATH}
					@rm -f ${PROG}

re:			fclean all

build-repo:
			@mkdir -p $(OBJPATH);

.PHONY: all clean fclean re bonus