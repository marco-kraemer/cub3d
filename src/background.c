/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:39:09 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	make_background(t_data img)
{
	t_aux	aux;
	int		sky;
	int		floor;

	aux.i = 0;
	aux.k = img.width / 2 - 524;
	sky = rgb(img.sky_color[0], img.sky_color[1], img.sky_color[2]);
	floor = rgb(img.floor_color[0], img.floor_color[1], img.floor_color[2]);
	if (aux.k < 0)
		aux.k = 0;
	while (aux.i < img.height / 2)
	{
		aux.j = 0;
		while (aux.j < img.width && aux.j < 1048)
			my_mlx_pixel_put(&img, aux.j++ + aux.k, aux.i, sky);
		aux.i++;
	}
	while (aux.i < img.height)
	{
		aux.j = 0;
		while (aux.j < img.width && aux.j < 1048)
			my_mlx_pixel_put(&img, aux.j++ + aux.k, aux.i, floor);
		aux.i++;
	}
}
