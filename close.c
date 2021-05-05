/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:46:03 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/03 23:05:42 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_map_error(t_data *img, int rule)
{
	if (rule == 0)
		printf("Must have 1 player!\n");
	if (rule == 1)
		printf("Invalid character on the map\n");
	if (rule == 2)
		printf("Invalid map\n");
	free(img->map_2d);
	free(img->map);
	free(img->file);
	exit(0);
	return (1);
}

int	close_win(t_data *img)
{
	free(img->tex[0]);
	free(img->tex[1]);
	free(img->tex[2]);
	free(img->tex[3]);
	free(img->tex[4]);
	free(img->map);
	free(img->file);
	free(img->map_2d);
	mlx_destroy_window(img->mlx, img->win);
	free(img->win);
	free(img->img);
	free(img->mlx);
	exit(0);
	return (1);
}
