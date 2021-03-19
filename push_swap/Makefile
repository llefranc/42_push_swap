# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/08 16:28:45 by llefranc          #+#    #+#              #
#    Updated: 2021/03/19 12:10:44 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap
CC			=	gcc
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror

SRCS		=	push_swap.c finding_median.c ../utils/manage_stack.c \
				../utils/stack_methods.c ../utils/check_and_errors.c

HEAD		=	headers.h libftprintf.h utils.h
PATH_HEAD	=	../includes/

OBJS	=	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
				$(CC) -o $(NAME) $(FLAGS) $(OBJS) ../libft_gnl_printf/libftprintf.a

$(OBJS)	:	$(addprefix $(PATH_HEAD), $(HEAD))

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<