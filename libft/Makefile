# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjamie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 20:37:30 by sjamie            #+#    #+#              #
#    Updated: 2019/09/11 20:37:32 by sjamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
DIR  = ./
SRC  = $(DIR)ft_atoi.c \
       $(DIR)ft_bzero.c \
       $(DIR)ft_isalpha.c\
       $(DIR)ft_isdigit.c\
       $(DIR)ft_isalnum.c\
       $(DIR)ft_isascii.c\
       $(DIR)ft_isprint.c\
       $(DIR)ft_toupper.c\
       $(DIR)ft_tolower.c\
       $(DIR)ft_itoa.c \
       $(DIR)ft_memalloc.c \
       $(DIR)ft_memccpy.c \
       $(DIR)ft_memcmp.c \
       $(DIR)ft_memcpy.c \
       $(DIR)ft_memdel.c \
       $(DIR)ft_memmove.c \
       $(DIR)ft_memset.c \
       $(DIR)ft_putchar.c \
       $(DIR)ft_putchar_fd.c \
       $(DIR)ft_putendl.c \
       $(DIR)ft_putendl_fd.c \
       $(DIR)ft_putnbr.c \
       $(DIR)ft_putnbr_fd.c \
       $(DIR)ft_putstr.c \
       $(DIR)ft_putstr_fd.c \
       $(DIR)ft_strcat.c \
       $(DIR)ft_strchr.c \
       $(DIR)ft_strclr.c \
       $(DIR)ft_strcmp.c \
       $(DIR)ft_strcpy.c \
       $(DIR)ft_strdel.c \
       $(DIR)ft_strdup.c \
       $(DIR)ft_strequ.c \
       $(DIR)ft_striter.c \
       $(DIR)ft_striteri.c \
       $(DIR)ft_strjoin.c \
       $(DIR)ft_strlcat.c \
       $(DIR)ft_strlen.c \
       $(DIR)ft_strmapi.c \
       $(DIR)ft_strncat.c \
       $(DIR)ft_strncmp.c \
       $(DIR)ft_strncpy.c \
       $(DIR)ft_strnequ.c \
       $(DIR)ft_strnew.c \
       $(DIR)ft_strnstr.c \
       $(DIR)ft_strrchr.c \
       $(DIR)ft_strsplit.c \
       $(DIR)ft_strstr.c \
       $(DIR)ft_strsub.c \
       $(DIR)ft_strtrim.c \
       $(DIR)ft_strmap.c \
       $(DIR)ft_lstnew.c \
       $(DIR)ft_lstdelone.c \
       $(DIR)ft_lstdel.c \
       $(DIR)ft_lstadd.c \
       $(DIR)ft_lstiter.c \
       $(DIR)ft_lstmap.c \
       $(DIR)ft_memchr.c


CC = gcc
CFLAGS = -Ofast -I ./includes/


OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
#	$(CC) -Wall -Wextra -Werror -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

