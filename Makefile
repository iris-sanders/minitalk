# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 16:10:38 by irsander          #+#    #+#              #
#    Updated: 2024/05/28 15:37:30 by irsander         ###   ########.fr        #
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

YELLOW = "\033[0;33m"
GREEN = "\033[0;32m"
RED = "\033[0;31m"
RESET = "\033[0m"

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	@echo $(YELLOW) "Compiling $(NAME_CLIENT)..." $(RESET)
	@$(MAKE) -C $(LIB_DIR)/libft
	@$(MAKE) -C $(LIB_DIR)/ft_printf
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCL) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)
	@echo $(GREEN) "$(NAME_CLIENT) compiled" $(RESET)

$(NAME_SERVER): $(OBJ_SERVER)
	@echo $(YELLOW) "Compiling $(NAME_SERVER)..." $(RESET)
	@$(MAKE) -C $(LIB_DIR)/libft
	@$(MAKE) -C $(LIB_DIR)/ft_printf
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCL) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)
	@echo $(GREEN) "$(NAME_SERVER) compiled" $(RESET)
	
$(OBJ_DIR):
	@echo $(YELLOW) "Creating objectfile directory" $(RESET)
	@mkdir -p $(OBJ_DIR)
	@echo $(GREEN) "Directory is created" $(RESET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo $(YELLOW) "Compiling $< into $@..." $(RESET)
	@$(CC) -c $< $(INCL) $(CFLAGS) -o $@
	@echo $(GREEN) "Compiled" $(RESET)

clean:
	@echo $(RED) "Cleaning up object files and directories..." $(RESET)
	@rm -rf $(OBJ_CLIENT) $(OBJ_SERVER)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIB_DIR)/ft_printf
	@$(MAKE) clean -C $(LIB_DIR)/libft
	@echo $(RED) "Clean completed" $(RESET)

fclean: clean
	@echo $(RED) "Performing full clean..." $(RESET)
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	@$(MAKE) fclean -C $(LIB_DIR)/libft
	@echo $(RED) "Full clean completed" $(RESET)

re: fclean all

.PHONY: all clean make fclean re

