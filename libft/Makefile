# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 16:03:37 by evmorvan          #+#    #+#              #
#    Updated: 2023/10/01 23:32:16 by evmorvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SOURCES =	$(addprefix sources/, \
				check/ft_isalnum.c check/ft_isalpha.c check/ft_isascii.c \
				check/ft_isdigit.c check/ft_isprint.c \
				converter/ft_atoi.c converter/ft_itoa.c converter/ft_tolower.c \
				converter/ft_toupper.c \
				io/utils/hex.c io/utils/number.c io/utils/pointer.c \
				io/utils/string.c io/utils/gnl.c io/ft_printf.c \
				io/ft_putchar_fd.c io/ft_putendl_fd.c io/ft_putnbr_fd.c \
				io/ft_putstr_fd.c io/get_next_line.c \
				memory/ft_bzero.c memory/ft_calloc.c memory/ft_memchr.c \
				memory/ft_memcmp.c memory/ft_memcpy.c memory/ft_memmove.c \
				memory/ft_memset.c memory/ft_strdup.c \
				string/ft_split.c string/ft_strchr.c string/ft_striteri.c \
				string/ft_strjoin.c string/ft_strlcat.c string/ft_strlcpy.c \
				string/ft_strlen.c string/ft_strmapi.c string/ft_strncmp.c \
				string/ft_strnstr.c string/ft_strrchr.c string/ft_strtrim.c \
				string/ft_substr.c \
				list/ft_lstadd_back.c list/ft_lstadd_front.c list/ft_lstclear.c \
				list/ft_lstdelone.c list/ft_lstiter.c list/ft_lstlast.c \
				list/ft_lstmap.c list/ft_lstnew.c list/ft_lstsize.c \
			)
OBJECTS	=	$(SOURCES:.c=.o)
CC		=	cc
HEADERS	=	includes/
CFLAGS	=	-Wall -Wextra -Werror -I $(HEADERS)

.c.o:
		$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME):	$(OBJECTS)
		ar rcs $(NAME) $(OBJECTS)
		ranlib $(NAME)

all:		$(NAME)

clean:
		rm -f $(OBJECTS) $(BO_OBJS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
