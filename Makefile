# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 09:44:11 by maraurel          #+#    #+#              #
#    Updated: 2021/05/04 15:10:13 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cub3d.c \
	background.c \
	bitmap.c \
	close.c \
	get_sky_floor.c \
	tex.c \
	get_color.c \
	get_resolution.c \
	init.c \
	map.c \
	map2.c \
	move.c \
	my_mlx_pixel_put.c \
	radius.c \
	radius2.c \
	sprites2.c \
	sprites.c \
	utils.c \
	walls.c

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

OBJS = $(SRC:.c=.o)

$(NAME): lib
	@$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $(SRC)
	@$(CC) $(FLAGS) $(OBJS) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz ./libft/libft.a -o $(NAME)

lib:
	@$(MAKE) -C libft
	
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft

clean: cleanlibft
	@$(RM) $(OBJS)
	@$(RM) *.bmp

cleanlibft:
	@$(MAKE) clean -C libft

re: fclean all

run: re
	@clear
	@./$(NAME) map.cub

memory: re
	@clear
	@ valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map.cub
git:
	git add .
	git commit -m "Update"
	git push