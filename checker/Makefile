# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 16:28:45 by llefranc          #+#    #+#              #
#    Updated: 2021/03/11 10:49:07 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	checker
CC			=	gcc
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror

SRCS		=	main.c ../utils/manage_stack.c ../utils/stack_methods.c

OBJS	=	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
				$(CC) -o $(NAME) $(FLAGS) $(OBJS) ../libft_gnl_printf/libftprintf.a

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<