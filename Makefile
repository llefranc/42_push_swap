# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 16:28:45 by llefranc          #+#    #+#              #
#    Updated: 2021/03/08 16:31:15 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	checker
CC			=	gcc
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror

SRCS		=	main.c

OBJS	=	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
				$(CC) -o $(NAME) $(FLAGS) $(OBJS) libftprintf.a

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<