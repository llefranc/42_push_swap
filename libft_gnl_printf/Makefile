# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 18:41:15 by llefranc          #+#    #+#              #
#    Updated: 2021/03/23 14:34:24 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
CC			=	gcc
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror

PF_SRCS		=	ft_fd_printf.c ft_printf.c ft_printf_fill_param.c ft_printf_fill_param2.c \
				ft_printf_fill_param3.c ft_printf_check_param.c \
				ft_printf_check_param2.c ft_printf_conv.c ft_printf_conv_cdi.c \
				ft_printf_conv_unp.c ft_printf_conv_x.c ft_printf_conv_s.c \
				ft_printf_conv_f.c ft_printf_conv_e.c ft_printf_conv_e2.c ft_printf_conv_g.c \
				ft_printf_conv_g2.c ft_printf_conv_lcls.c ft_printf_conv_others.c \
				big_int_add.c big_int_subs.c big_int_subs2.c big_int_mult_pow.c \
				big_int_div.c big_ints_init.c big_ints_calc.c print_bits.c \
				double_to_char.c double_to_char2.c round_dblstr.c round_dblstr2.c \
				wchar_conv.c wchar.c
LB_SRCS		=	ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_pow.c \
				ft_memccpy.c ft_memcmp.c ft_memmove.c ft_strchr.c \
				ft_strlcat.c ft_strlen.c ft_strnstr.c ft_tolower.c \
				ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strisdigit.c \
				ft_memchr.c ft_memcpy.c ft_memset.c ft_strdup.c \
				ft_strlcpy.c ft_strncmp.c ft_strrchr.c ft_toupper.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_free_split.c \
				ft_itoa.c ft_itoa_base.c ft_itoa_buffer.c ft_itoa_buffer_uns.c \
				ft_itoa_base_buffer_uns.c ft_strmapi.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c \
				ft_convert_base.c ft_convert_base2.c ft_replace_char.c
GNL_SRCS	=	get_next_line.c get_next_line_utils.c

PF_OBJS		=	$(PF_SRCS:.c=.o)
LB_OBJS		=	$(LB_SRCS:.c=.o)
GNL_OBJS	=	$(GNL_SRCS:.c=.o)

PF_PATH		=	srcs_printf/
LB_PATH		=	srcs_libft/
GNL_PATH	=	srcs_gnl/

all		: 	$(NAME)

$(NAME)	:	$(addprefix $(PF_PATH), $(PF_OBJS)) $(addprefix $(GNL_PATH), $(GNL_OBJS)) \
			$(addprefix $(LB_PATH), $(LB_OBJS))
			ar rc $(NAME) $(addprefix $(PF_PATH), $(PF_OBJS)) $(addprefix $(GNL_PATH), $(GNL_OBJS)) \
			$(addprefix $(LB_PATH), $(LB_OBJS))
			ranlib $(NAME)

clean	:	
				rm -rf $(addprefix $(PF_PATH), $(PF_OBJS)) $(addprefix $(GNL_PATH), $(GNL_OBJS)) \
				$(addprefix $(LB_PATH), $(LB_OBJS))

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<
