# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:08:02 by evmorvan          #+#    #+#              #
#    Updated: 2023/09/18 15:49:24 by evmorvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -O0

SRCS		=	$(addprefix sources/, \
					minishell.c parser/parser.c lexer/lexer.c \
					utils/split_lexer.c utils/ft_epurstr.c \
					executor/executor.c env/env.c utils/node.c \
					builtins/echo.c builtins/env.c builtins/pwd.c \
					builtins/unset.c builtins/cd.c utils/ft_strtrim_lexer.c \
					builtins/export.c builtins/exit.c expander/expander.c \
					env/env2.c lexer/quote.c utils/debug.c signals/signals.c \
					lexer/memory.c utils/misc.c \
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
