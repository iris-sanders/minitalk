# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 16:10:38 by irsander          #+#    #+#              #
#    Updated: 2024/05/28 14:09:02 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB_DIR = lib
OBJ_DIR = src/obj
SRC_DIR = src

INCL = -I ./incl -I $(LIB_DIR)/libft -I $(LIB_DIR)/ft_printf

FILES_CLIENT =	client.c
FILES_SERVER =	server.c \
				vec.c \

SRC = $(addprefix $(SRC_DIR)/, $(FILES_CLIENT))
SRC = $(addprefix $(SRC_DIR)/, $(FILES_SERVER))
OBJ_CLIENT = $(addprefix $(OBJ_DIR)/, $(FILES_CLIENT:.c=.o))
OBJ_SERVER = $(addprefix $(OBJ_DIR)/, $(FILES_SERVER:.c=.o))

LIBFT = $(LIB_DIR)/libft/libft.a
PRINTF = $(LIB_DIR)/ft_printf/libftprintf.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/ft_printf
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCL) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/ft_printf
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCL) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< $(INCL) $(CFLAGS) -o $@

clean:
	rm -rf $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)/ft_printf
	$(MAKE) clean -C $(LIB_DIR)/libft

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	$(MAKE) fclean -C $(LIB_DIR)/libft

re: fclean all

.PHONY: all clean make fclean re

