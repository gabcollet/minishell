# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 12:58:26 by gcollet           #+#    #+#              #
#    Updated: 2021/10/26 11:03:02 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

OBJPATH = obj/

SRCS 	= ft_isalnum.c ft_isdigit.c ft_memccpy.c ft_memcpy.c ft_putchar_fd.c\
		ft_putstr_fd.c ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c\
		ft_toupper.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memchr.c\
		ft_memmove.c ft_putendl_fd.c ft_split.c ft_strjoin.c ft_strlen.c\
		ft_strnstr.c ft_substr.c ft_atoi.c ft_calloc.c ft_isascii.c ft_itoa.c\
		ft_memcmp.c ft_memset.c ft_putnbr_fd.c ft_strchr.c ft_strlcat.c\
		ft_strmapi.c ft_strrchr.c ft_tolower.c ft_atof.c ft_strcmp.c ft_atol.c\
		dlst_last.c dlst_len.c dlst_add_back.c dlst_add_front.c dlst_new.c ft_isint.c\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
		ft_sort_tab.c ft_free_tab.c ft_strjoin_free_s1.c ft_atoll.c

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJPATH), $(OBJFILES))
VPATH   = ./

HEADER	= libft.h

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

all:		build-repo	${NAME}

$(NAME):	${OBJS}
					@ar rc ${NAME} ${OBJS}

${OBJPATH}%.o:%.c
					@gcc ${CFLAGS} -o $@ -c $<

clean:
					@rm -f ${OBJS}

fclean: 	clean
					@rm -f $(NAME)
					@rm -rf ${OBJPATH}

re:			fclean all

build-repo:
			@mkdir -p $(OBJPATH);

.PHONY: all clean fclean re