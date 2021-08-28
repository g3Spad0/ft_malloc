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


NAME =		libft_malloc_$(HOSTTYPE).so
SL_NAME =	libft_malloc.so
CC =		gcc
CFLAGS = 	-Wall -Wextra -Werror

INC_DIR =	includes/
SRC_DIR =	src/
BIN_DIR =	bin/

SRC_FILES  =   check_pointer.c \
			   common.c \
			   large_free.c \
			   large_malloc.c \
			   libft.c \
			   printers.c \
			   show_alloc_mem.c \
			   show_alloc_mem_ex.c \
			   small_free.c \
			   small_malloc.c \
			   small_malloc_norm.c \
			   tiny_free.c \
			   tiny_malloc.c \
			   utils.c \
			   realloc.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BINS = $(addprefix $(BIN_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(BINS)
	$(CC) $(CFLAGS) $(BINS) -shared -fPIC -o $(NAME)
	ln -fs ${NAME} ${SL_NAME}

$(BIN_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)/ft_malloc.h Makefile
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(BIN_DIR):
	mkdir -p bin

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(SL_NAME)

re: fclean all

.PHONY: all re run clean fclean
