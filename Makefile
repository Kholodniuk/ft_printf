# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skholodn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 17:33:06 by skholodn          #+#    #+#              #
#    Updated: 2017/03/18 03:42:28 by skholodn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ft_printf.h

SRCS = ft_printf.c \
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
	   ft_tolower.c \
	   get_wstr.c \
	   get_n.c \
	   parse_colors.c \
	   float_double.c \
	   non_printable.c \
	   get_iso_data.c \
	   get_binary.c \
	   parse_fd.c \
	   lib_printf1.c \
	   ft_strchr.c \
	   ft_strcpy.c \
	   ft_strcat.c


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

