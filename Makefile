# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yazhu <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 16:09:18 by yazhu             #+#    #+#              #
#    Updated: 2018/01/25 18:47:07 by yazhu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
SRCS	= main.c errors.c read_data.c populate_data.c putnstr_fd.c permutate.c \
		base64.c des.c des_processes.c get_permutate_subkeys.c   
OFILES	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	cd libft && make
	gcc -Wall -Wextra -Werror -o $(NAME) $(SRCS) -L ./libft -lft

clean:
	cd libft && make clean
	/bin/rm -f $(OFILES)

fclean: clean
	cd libft && make fclean
	/bin/rm -f $(NAME)

re: fclean all
