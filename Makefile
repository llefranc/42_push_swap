# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 16:59:51 by llefranc          #+#    #+#              #
#    Updated: 2021/03/23 17:03:08 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PS		=	push_swap
NAME_CH		=	checker
CC			=	gcc
FLAGS		=	-g3 -fsanitize=address -Wall -Wextra -Werror

SOURCES_CH	=	checker.c
SOURCES_PS	=	push_swap.c finding_median.c stack_sizes.c quicksort.c push_to_stack.c opti.c \
				sort_small_stack.c
SOURCES_UT	=	manage_stack.c stack_methods.c check_and_errors.c

PATH_CH		=	srcs_checker/
PATH_PS		=	srcs_push_swap/
PATH_UT		=	utils/

SRCS_CH		=	$(addprefix $(PATH_CH), $(SOURCES_CH))
SRCS_PS		=	$(addprefix $(PATH_PS), $(SOURCES_PS))
SRCS_UT		=	$(addprefix $(PATH_UT), $(SOURCES_UT))

HEAD		=	headers.h libftprintf.h utils.h push_swap.h
PATH_HEAD	=	includes/

OBJS_CH		=	$(SRCS_CH:.c=.o)
OBJS_PS		=	$(SRCS_PS:.c=.o)
OBJS_UT		=	$(SRCS_UT:.c=.o)

all			: 	$(NAME_PS) $(NAME_CH)

$(NAME_CH)	:	$(OBJS_CH) $(OBJS_UT)
				make -C libft_gnl_printf 
				$(CC) -o $(NAME_CH) $(FLAGS) $(OBJS_CH) $(OBJS_UT) libft_gnl_printf/libftprintf.a

$(NAME_PS)	:	$(OBJS_PS) $(OBJS_UT)
				make -C libft_gnl_printf
				$(CC) -o $(NAME_PS) $(FLAGS) $(OBJS_PS) $(OBJS_UT) libft_gnl_printf/libftprintf.a

$(OBJS)		:	$(addprefix $(PATH_HEAD), $(HEAD))

clean		:
				make clean -C libft_gnl_printf
				rm -rf $(OBJS_CH) $(OBJS_UT) $(OBJS_PS)

fclean		:	clean
					make fclean -C libft_gnl_printf
					rm -rf ./checker ./push_swap

re			:	fclean all

.PHONY		:	all clean fclean re

%.o			:	%.c
				$(CC) $(FLAGS) -o $@ -c $<