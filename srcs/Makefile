PROG	= test

SRCS 	= ms_cd.c free_func.c env.c utils.c 

OBJS 	= ${SRCS:.c=.o}

HEADER	= -I../includes -I../libft

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

.c.o:		
					@$(CC) ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:	${PROG}

${PROG}:	${OBJS}
					@make re -C ../libft
					@$(CC) ${OBJS} -L ../libft -l ft -o ${PROG} -lreadline 
					@echo "\n\033[32m\033[1mtest compiled\n\033[0m"

clean:
					@make clean -C ../libft
					@rm -rf ${OBJS}

fclean: 	clean
					@make fclean -C ../libft
					@rm -f ${PROG}

re:			fclean all


.PHONY: all clean fclean re bonus