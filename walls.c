/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:26:36 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 22:35:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_data img, float lineHeight, int color[64][64]
	, float first_pixel)
{
	t_aux		aux;
	static int	i;

	aux.m = -1;
	aux.oldstep = 1;
	aux.k = img.width / 2 - 524;
	aux.j = img.height / 2 - lineHeight / 2;
	aux.increaseY = 0;
	aux.i = 0;
	if (aux.k < 0)
		aux.k = 0;
	while (aux.m < lineHeight)
	{
		while (aux.i < first_pixel)
			aux.i++;
		aux.i--;
		while (aux.i++ <= img.step * aux.oldstep && aux.m++ < lineHeight)
			my_mlx_pixel_put(&img, aux.k + i, aux.j + aux.m,
				color[img.texX][aux.increaseY]);
		aux.increaseY++;
		aux.oldstep++;
	}
	i++;
	if (i == img.width || i == 1048)
		i = 0;
}

void	get_first_pixel(t_data img, float lineHeight, int color[64][64])
{
	float	first_pixel;

	first_pixel = 0;
	img.step = (float) lineHeight / 64;
	if (lineHeight > img.height)
	{
		first_pixel = lineHeight - img.height;
		first_pixel = first_pixel / 2;
		lineHeight = img.height;
	}
	draw_walls(img, lineHeight, color, first_pixel);
}

void	choose_tex(t_data img, float lineHeight, int color[4][64][64])
{
	int		c;

	if (img.pa > 2 * PI)
		img.pa -= 2 * PI;
	if (img.pa < 0)
		img.pa += 0;
	if (img.hit == 0 && ((img.pa < PI / 2 && img.pa > 0)
			|| (img.pa < 2 * PI && img.pa > 4.71)))
		c = 0;
	else if (img.hit == 0)
		c = 1;
	else if (img.pa > PI && img.pa < 2 * PI)
		c = 2;
	else
		c = 3;
	get_first_pixel(img, lineHeight, color[c]);
}

void	make_textures(t_data img, int color[4][64][64], float radius)
{
	t_aux	aux;

	aux.lineHeight = (1080 / radius * 20);
	if (img.hit == 1)
		aux.wallX = img.px + cos(img.pa) * radius;
	else
		aux.wallX = img.py + sin(img.pa) * radius;
	while (aux.wallX > img.map_height)
		aux.wallX -= img.map_height;
	img.step = (float) img.map_height / 64;
	aux.oldstep = 0;
	while (img.step * aux.oldstep <= aux.wallX)
		aux.oldstep++;
	aux.increaseX = 0;
	img.texX = 0;
	while (aux.increaseX <= img.step * aux.oldstep)
	{
		img.texX++;
		aux.increaseX += img.step;
	}
	if (img.texX >= 64)
		img.texX = 63;
	img.texX -= 2;
	choose_tex(img, aux.lineHeight, color);
}

void	make_walls(t_data img, float radius, float pa, int color[4][64][64])
{
	float	ca;

	ca = pa - img.pa;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	radius = radius * cos(ca);
	if (radius < 0)
		radius = radius * (-1);
	make_textures(img, color, radius);
}
