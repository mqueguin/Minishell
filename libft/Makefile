# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 19:01:04 by tale-fau          #+#    #+#              #
#    Updated: 2022/02/27 23:12:37 by mqueguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;91m
GREEN = \033[0;92m
BLUE = \033[0;34m
WHITE = \x1b[0m

NAME		=	libft.a

SRCS		=	ft_atoi.c\
			ft_memset.c \
			ft_memcpy.c \
			ft_free_tab.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_tablen.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_strncmp_check_len.c \
			ft_strncpy.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strnstr.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strjoinfree.c \
			ft_swap.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_free_tab.c \
			ft_putnbr.c \
			ft_strdel.c

HEAD		= libft.h

OBJS		= ${SRCS:%.c=${OBJS_DIR}/%.o}

OBJS_DIR	= ./objs

NAME		= libft.a

CC		= clang

RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror

${OBJS_DIR}/%.o: %.c
		@mkdir -p ${OBJS_DIR}
		@${CC} ${CFLAGS} -I. -c $< -o $@

$(NAME):	${OBJS}
		@ar rc ${NAME} ${OBJS}

all:		${NAME}

clean:
		@${RM} ${OBJS} ${OBJS_BONUS}
		@rm -rf ${OBJS_DIR}

fclean:		clean
		@${RM} ${NAME}

re:		fclean all

.PHONY:		all    clean    fclean re bonus
