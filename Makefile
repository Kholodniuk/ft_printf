# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skholodn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 17:33:06 by skholodn          #+#    #+#              #
#    Updated: 2017/03/11 18:14:33 by skholodn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ft_printf.h

SRCS = ft_printf.c \
		lib_printf1.c \
		ft_bzero.c \
		ft_strcat.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strnew.c \
		parse_persent.c \
		ft_atoi.c \
		itoa_base.c \
		di.c \
		get_str.c \
		oxp.c \
		u.c \
		apply_printf.c \
		apply_width.c \
		char_wchar.c \
		ft_memcpy.c \
		ft_strcpy.c \
		ft_tolower.c \
		ft_strncpy.c \
		get_wstr.c \
		ft_strsub.c \
		ft_strchr.c \


OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -cru $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< -I $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	rm -f $(NAME)
	make all

