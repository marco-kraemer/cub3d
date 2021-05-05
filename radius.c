/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radius.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:04:18 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 14:15:40 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finish_dda(t_data *img, int stepX, int stepY, t_aux aux)
{
	img->hit = 0;
	while (*(img->map_2d + aux.i + aux.j * get_width_minmap(*img)) != '1')
	{
		if (img->side_distX < img->side_distY)
		{
			img->side_distX += img->delta_distX;
			aux.i += stepX;
			img->hit = 0;
		}
		else
		{
			img->side_distY += img->delta_distY;
			aux.j += stepY;
			img->hit = 1;
		}
	}
}

void	continue_dda(t_data *img, int stepX, int stepY)
{
	t_aux	aux;

	aux.i = 0;
	aux.j = 0;
	aux.k = img->map_height;
	while (aux.k < img->py)
	{
		aux.k += img->map_height;
		aux.j++;
	}
	aux.k = img->map_width;
	while (aux.k < img->px)
	{
		aux.k += img->map_width;
		aux.i++;
	}
	finish_dda(img, stepX, stepY, aux);
}

void	start_dda(t_data *img)
{
	int	stepX;
	int	stepY;

	if (img->pa < 2 * PI && img->pa > 3 * PI / 2)
	{
		stepX = 1;
		stepY = -1;
	}
	else if (img->pa < 3 * PI / 2 && img->pa > PI)
	{
		stepX = -1;
		stepY = -1;
	}
	else if (img->pa < PI && img->pa > PI / 2)
	{
		stepX = -1;
		stepY = 1;
	}
	else
	{
		stepX = 1;
		stepY = 1;
	}
	continue_dda(img, stepX, stepY);
}

int	return_values(int buf, t_data *img
	, float oldpa, int color[4][64][64])
{
	if (img->hit == 0)
	{
		img->zBuffer[buf] = img->side_distX - img->delta_distX;
		make_walls(*img, img->side_distX - img->delta_distX, oldpa, color);
		return (img->side_distX - img->delta_distX);
	}
	else
	{
		img->zBuffer[buf] = img->side_distY - img->delta_distY;
		make_walls(*img, img->side_distY - img->delta_distY, oldpa, color);
		return (img->side_distY - img->delta_distY);
	}
}

int	radius_size(t_data *img, float oldpa,
	int color[4][64][64])
{
	static int	buf;

	img->side_distY = find_side_distY(*img);
	img->side_distX = find_side_distX(*img);
	img->delta_distX = (img->min_map_width /get_width_minmap(*img))
		/ cos(img->pa);
	img->delta_distY = (img->min_map_height / get_height_minmap(*img))
		/ sin(img->pa);
	if (img->delta_distX < 0)
		img->delta_distX = img->delta_distX * (-1);
	if (img->delta_distY < 0)
		img->delta_distY = img->delta_distY * (-1);
	start_dda(img);
	if (buf == 1048 || buf == img->width)
		buf = 0;
	buf++;
	return (return_values(buf, img, oldpa, color));
}
