/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radius2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:31:48 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	find_side_distX (t_data img)
{
	t_aux	aux;
	float	side_distX;

	aux.i = img.map_width;
	if ((img.pa > (3 * PI) / 2 && img.pa > 0)
		|| (img.pa > 0 && img.pa < PI / 2))
	{
		while (aux.i < img.px)
			aux.i += img.map_width;
		side_distX = aux.i - img.px;
	}
	else
	{
		while (aux.i < img.px - img.min_map_width / get_width_minmap(img))
			aux.i += img.map_width;
		side_distX = -1 * (aux.i - img.px);
	}
	side_distX = side_distX / cos(img.pa);
	if (side_distX < 0)
		side_distX = side_distX * (-1);
	if (side_distX == 0)
		side_distX = 0;
	return (side_distX);
}

float	find_side_distY (t_data img)
{
	t_aux	aux;
	float	side_distY;

	aux.j = img.map_height;
	if (img.pa <= 2 * PI && img.pa > PI)
	{
		while (aux.j < img.py - img.min_map_height / get_height_minmap(img))
			aux.j += img.map_height;
		side_distY = -1 * (aux.j - img.py);
	}
	else
	{
		while (aux.j < img.py)
			aux.j += img.map_height;
		side_distY = aux.j - img.py;
	}
	side_distY = side_distY / sin(img.pa);
	if (side_distY < 0)
		side_distY = side_distY * (-1);
	if (side_distY == 0)
		side_distY = 0;
	return (side_distY);
}
