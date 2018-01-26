# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yazhu <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/27 10:32:40 by yazhu             #+#    #+#              #
#    Updated: 2018/01/25 18:36:42 by yazhu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFILES	= ft_bzero.c ft_memalloc.c ft_memcpy.c ft_putchar.c ft_putchar_fd.c \
		  ft_putendl.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_power.c
OFILES	= $(CFILES:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -c $(CFILES)
	@ar rc $(NAME) $(OFILES)

clean:
	@/bin/rm -f $(OFILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
