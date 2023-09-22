#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 11:08:02 by evmorvan          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/09/21 21:59:18 by evmorvan         ###   ########.fr        #
=======
#    Updated: 2023/09/21 01:14:52 by sfernand         ###   ########.fr        #
>>>>>>> 3435e2ad2dda4acd05c971e1edb6fd17ec46772c
#                                                                              #
#******************************************************************************#

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g

SRCS		=	$(addprefix sources/, \
					minishell.c lexer/lexer.c \
					utils/split_lexer.c utils/ft_epurstr.c \
					env/env.c utils/node.c \
					builtins/echo.c builtins/env.c builtins/pwd.c \
					builtins/unset.c builtins/cd.c utils/ft_strtrim_lexer.c \
					builtins/export.c builtins/exit.c expander/expander.c \
					env/env2.c lexer/quote.c utils/debug.c signals/signals.c \
					lexer/memory.c utils/misc.c utils/random.c utils/quotes.c \
					parser/parser.c parser/utils.c parser/heredoc.c \
					executor/executor.c executor/utils.c executor/misc.c \
					utils/ft_add_space.c \
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
