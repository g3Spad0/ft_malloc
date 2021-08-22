# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjamie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 18:54:40 by sjamie            #+#    #+#              #
#    Updated: 2021/08/22 18:54:43 by sjamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

DIR  = ./src/
SRC  = $(DIR)check_pointer.c \
       $(DIR)common.c \
       $(DIR)large_free.c \
       $(DIR)large_malloc.c \
       $(DIR)libft.c \
       $(DIR)printers.c \
       $(DIR)show_alloc_mem.c \
       $(DIR)show_alloc_mem_ex.c \
       $(DIR)small_free.c \
       $(DIR)small_malloc.c \
       $(DIR)small_malloc_norm.c \
       $(DIR)tiny_free.c \
       $(DIR)tiny_malloc.c \
       $(DIR)utils.c



CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./includes/


OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -shared -fPIC -o $(NAME)
	/bin/rm -f $(LINK)
	ln -s $(NAME) $(LINK)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME) $(LINK)

re: fclean all
