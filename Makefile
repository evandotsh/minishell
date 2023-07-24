# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:08:02 by evmorvan          #+#    #+#              #
#    Updated: 2023/07/22 12:58:56 by sfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g

SRCS		=	$(addprefix sources/, \
					builtins/debug.c utils/env.c utils/misc.c minishell.c \
					executor/executor.c parser/parser.c lexer/lexer.c \
					expander/expander.c utils/split_lexer.c \
					utils/ft_epurstr.c  parser/redir.c \
				)
OBJS	=	${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	$(MAKE) -C ./libft
	${CC} ${OBJS} -o ${NAME} libft/libft.a -lreadline

all:	${NAME}


clean:
	${MAKE} -C ./libft clean
	rm -f ${OBJS}

fclean:	clean
	${MAKE} -C ./libft fclean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
