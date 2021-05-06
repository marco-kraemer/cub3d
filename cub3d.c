/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:47:45 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/06 10:55:35 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walls(t_data *img, int color[4][64][64])
{
	int		rays;
	float	oldpa;
	float	fix;

	fix = (float) img->width / 2 / 1000;
	if (fix > 0.524)
		fix = 0.524;
	oldpa = img->pa;
	img->pa = img->pa - fix;
	if (img->pa < 0)
	{
		img->pa += 2 * PI;
		oldpa += 2 * PI;
	}
	rays = 0;
	while (rays < img->width && rays < 1048)
	{
		rays++;
		radius_size(img, oldpa, color);
		img->pa += 0.001;
	}
	img->pa = oldpa;
}

void	print_images(t_data *img)
{
	static int	i;
	static int	color[5][64][64];

	if (i == 0)
	{
		get_textures(img, color);
		i++;
	}
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr
		(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	make_background(*img);
	walls(img, color);
	sprites(*img, color);
	if (img->rule == 1)
	{
		bitmap(img);
		exit (0);
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	mlx_destroy_image(img->mlx, img->img);
}

int	loop(t_data *img)
{
	move_player(img);
	print_images(img);
	return (0);
}

void	start_cub(t_data *img, int argc, char *argv[])
{
	img->mlx = mlx_init();
	img->min_map_height = img->map_height * get_height_minmap(*img);
	img->min_map_width = img->map_width * get_width_minmap(*img);
	if (argc == 2)
	{
		img->win = mlx_new_window(img->mlx, img->width, img->height, "cub3D");
		mlx_hook(img->win, 2, 1L << 0, key_press, img);
		mlx_hook(img->win, 3, 1L << 1, key_release, img);
		mlx_hook(img->win, 33, 1L << 17, close_win, img);
		mlx_loop_hook(img->mlx, loop, img);
	}
	else if (argc == 3 && check_argv(argv[2]) == 1)
	{
		img->rule = 1;
		print_images(img);
		exit (1);
	}
	else
	{
		printf("Invalid argument!\n");
		exit (0);
	}
	mlx_loop(img->mlx);
}

int	main(int argc, char *argv[])
{
	t_data	img;
	int		i;

	img.map_height = 25;
	img.map_width = 25;
	get_file(&img, argv);
	printf("Starting cub3D...\n");
	img.height = get_res_height(img);
	img.width = get_res_width(img);
	if (img.height <= 0 || img.width <= 0)
		close_map_error(&img, 3);
	img.map = get_map(img, img.file);
	map_array_2d(&img);
	i = -1;
	while (i++ < 4)
		img.path_to_tex[i] = get_tex_path(img.file, i);
	i = -1;
	while (i++ < 2)
	{
		img.sky_color[i] = get_sky_color(img.file, i);
		img.floor_color[i] = get_floor_color(img.file, i);
	}
	init_player(&img);
	start_cub(&img, argc, argv);
	return (0);
}
