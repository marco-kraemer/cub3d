/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:29:55 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:40:09 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "../libft/libft.h"

# define	PI		3.1415926535
# define	FOV_ANGLE	1.04719
# define	TILE_SIZE	64

typedef struct s_data {
	int		min_map_width;
	int		min_map_height;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*mlx;
	void	*win;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pda;
	float	pa;
	int		side;

	char	*map;
	char	*file;
	char	*map_2d;
	char	*path_to_tex[5];
	int		sky_color[3];
	int		floor_color[3];
	int		width;
	int		height;

	float	side_distX;
	float	side_distY;
	float	delta_distX;
	float	delta_distY;
	int		hit;
	int		buf;

	int		*visibles;
	int		numVisibleSprites;
	float	perpDistance;
	float	spriteHeight;
	float	spriteWidth;
	float	spriteTopY;
	float	spriteBottomY;
	float	spriteAngle;
	float	spriteScreenPosX;
	float	spriteLeftX;
	float	spriteRightX;
	float	first_pixel;
	float	texStep;
	int		spriteTexX;
	int		spriteTexY;
	float	check_tex_width;
	int		select;
	float	zBuffer[1048];

	int		texX;
	float	step;

	int		map_height;
	int		map_width;

	int		rule;
	void	*tex[5];

	int		array_length;

	int		a;
	int		s;
	int		w;
	int		d;
	int		right;
	int		left;
	int		esc;
}		t_data;

typedef struct s_aux {
	int		i;
	int		j;
	int		k;
	int		m;
	int		oldstep;
	int		increaseY;
	float	coordX;
	float	coordY;
	float	wallX;
	float	increaseX;
	float	lineHeight;
}		t_aux;

int		check_argv(char *arg);
int		get_floor_color(char *file, int count);
int		get_sky_color(char *file, int count);
int		get_color(t_data *data, int x, int y);
int		get_res_width(t_data img);
int		get_res_height(t_data img);
int		check_move(t_data img);
int		move_player(t_data *img);
int		radius_size(t_data *img, float oldpa, int color[4][64][64]);
int		sprite_data(t_data img, float sprites[][3]);
int		get_height_minmap(t_data img);
int		get_width_minmap(t_data img);
int		close_win(t_data *img);
int		close_map_error(t_data *img, int rule);
int		rgb(int r, int g, int b);
int		bitmap(t_data *img);
int		check_argv2(char *arg);
int		key_release(int keycode, t_data *img);
int		key_press(int keycode, t_data *img);

char	*get_map(t_data img, char *file);
void	get_file(t_data *img, char *argv[]);
char	*get_tex_path(char *file, int count);

void	map_array_2d(t_data *img);
void	make_background(t_data img);
void	print_images(t_data *img);
void	init_player(t_data *img);
void	draw_vector(t_data img);
void	draw_player(t_data img);
void	minmap_background(t_data img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	make_sprites(t_data img, int numSprites,
			int color[4][64][64], float sprites[][3]);
void	sprites(t_data img, int color[4][64][64]);
void	make_walls(t_data img, float radius, float pa, int color[4][64][64]);
void	walls(t_data *img, int color[4][64][64]);
void	sort_sprites(float sprites[100000][3], int numSprites);
void	get_sprite_datas(t_data *img,
			float sprites[get_width_minmap(*img)*get_height_minmap(*img)][3]);
void	get_tex_datas(t_data *img);
void	draw_sprites2(t_data img, float sprites[100000][3],
			int color[4][64][64], t_aux aux);
void	draw_sprites(t_data img, float sprites[100000][3],
			int color[4][64][64]);
void	get_textures(t_data *img, int color[5][64][64]);
void	check_last_line(t_data *img, int length);
void	check_first_line(t_data *img, int length);

float	find_side_distY (t_data img);
float	find_side_distX (t_data img);

#endif