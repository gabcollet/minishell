# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 19:56:08 by gcollet           #+#    #+#              #
#    Updated: 2021/11/25 12:17:32 by jbadia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CWHITEBG  = \033[47m
CBLUE2   = \033[34m
CEND      = \033[0m
CBOLD     = \033[1m
CYELLOW = \033[33m
COLOR = $(CBLUE2)$(CBOLD)
TALK = $(CBOLD) $(CYELLOW)

PROG	= minishell

OBJPATH = obj/


SRCS 	= 	main.c env.c free_func.c token_utils.c token_list_utils.c parser.c\
			init.c utils.c ms_env.c ms_export.c ms_cd.c ms_echo.c ms_exit.c\
			ms_pwd.c ms_unset.c ms_builtins.c  exec_utils.c  error.c\
      		parser_utils.c ms_quote.c  ms_job.c  ms_job_list.c\
			dollar.c exec.c exec_redir.c heredoc.c signal.c \
			replace_tild_w_home.c syntax.c syntax_2.c dollar_utils.c replace_dol_w_env.c\
			ms_quote_utils.c dollar_utils2.c

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJPATH), $(OBJFILES)) 
VPATH   = srcs srcs/builtins srcs/parsing srcs/exec  srcs/parsing/dollar srcs/parsing/job\
		srcs/parsing/parser srcs/parsing/syntax srcs/parsing/tokens

HEADER	= -Iincludes -Ilibft

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

all:	build-repo ${PROG}

	@echo "$(COLOR)	             xxxxx"
	@echo "                  xXXXXXXXXXx"
	@echo "                 XXXXXXXXXXXXX"
	@echo "                xXXXXXXXX  XXXx"
	@echo "                XXXXXXXXX 0XXXX___"
	@echo "               xXXXXXXXXXxxXXXX____\\   $(TALK) MINISHELL COMPILED$(CEND)$(COLOR)	"
	@echo "               XXXXXXXXXXXXXXXX____/"
	@echo "               XXXXXXXXXXXXXXXXX"
	@echo "               XXXXX|\XXX/|XXXXX"
	@echo "               XXXXX| \-/ |XXXXX"
	@echo "              xXXXXX| [ ] |XXXXXx"
	@echo "            xXXXX   | /-\ |   XXXXx"
	@echo "         xXXXXX     |/   \|     XXXXXx"
	@echo "       xXXXXXX                   XXXXXXx"
	@echo "      xXXXXXXX                   XXXXXXXx"
	@echo "     xXXXXXXXX                   XXXXXXXXx"
	@echo "    xXXXXXXXXX                   XXXXXXXXXx"
	@echo "   xXXXXXXXXXX                   XXXXXXXXXXx"
	@echo "  xXXXXXXXXXXX                   XXXXXXXXXXXx"
	@echo " xXXXXXXXX XXX                   XXX XXXXXXXXx"
	@echo " XXXXXXXX  XXX                   XXX  XXXXXXXX"
	@echo "xXXXXXXX   XXX                   XXX   XXXXXXXx"
	@echo "XXXXXX     XXX                   XXX     XXXXXX"
	@echo "XXXX       XXX                   XXX       XXXX"
	@echo " XX        XXX                   XXX        XX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXXx                 xXXX"
	@echo "           XXXXXXXXXXXXXXXXXXXXXXXXX"
	@echo "           XXXXXXX           XXXXXXX"
	@echo "       ____XXXXXX             XXXXXX____"
	@echo "      /________/               \________\\ $(CEND)"

${PROG}:	${OBJS}
					@make re -C ./libft
					@stty -echoctl
					@$(CC) ${OBJS} -Llibft -Llib -l ft -o ${PROG} -lreadline -lcurses
					@echo "\n\033[32m\033[1mMinishell ALPHA v-1.1 Compiled!\n\033[0m"

${OBJPATH}%.o:%.c
					@gcc ${CFLAGS} ${HEADER} -o $@ -c $<

linux:	${OBJS}
					@make re -C ./libft
					@stty -echoctl
					@$(CC) ${OBJS} -Llibft -l ft -o ${PROG} -lreadline
					@echo "\n\033[32m\033[1mMinishell ALPHA v-1.1 Compiled!\n\033[0m"

norm:
		@find . -name "*.c" -o -name "*.h" | sed s'/\.\///g' | awk '{print $$1": OK!"; system("sleep 0.03");};'
	
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