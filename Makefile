# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 09:44:11 by maraurel          #+#    #+#              #
#    Updated: 2022/02/09 16:00:58 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_PATH = ./src

OBJ_PATH = ./obj

SRC = $(notdir $(wildcard ./src/*.c))

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(FLAGS) $(OBJ) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm ./libft/libft.a -o $(NAME)
	@echo "Installation completed"
	@echo "Run './cub3d <map_path>'"

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@echo "Building cub3d....."
	@$(CC) -g $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft

clean:
	@$(MAKE) clean -C libft
	@$(RM) $(OBJ_PATH)/*.o

re: fclean all

run: all
	@./$(NAME)

git:
	git add .
	git commit -m "Update"
	git push

memory: re
	@clear
	@ valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map.cub