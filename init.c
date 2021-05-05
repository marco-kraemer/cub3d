/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:38:34 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 15:19:40 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_location (t_data *img, char *map_arr, int width, t_aux aux)
{
	char	c;

	while (img->map[aux.k])
	{
		*(map_arr + aux.i + aux.j * width) = *(img->map + aux.k);
		c = *(map_arr + aux.i + aux.j * width);
		if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
		{
			img->px = aux.i * img->map_height + (img->map_height / 2);
			img->py = aux.j * img->map_width + (img->map_width / 2);
			break ;
		}
		if (img->map[aux.k] == '\n')
		{
			aux.j++;
			aux.k++;
			aux.i = 0;
		}
		aux.i++;
		aux.k++;
	}
	return (c);
}

void	init_player(t_data *img)
{
	char	*map_arr;
	int		width;
	char	c;
	t_aux	aux;

	aux.i = 0;
	aux.j = 0;
	aux.k = 0;
	width = get_width_minmap(*img);
	map_arr = malloc(width * get_height_minmap(*img) * sizeof (char));
	c = get_location(img, map_arr, width, aux);
	if (c == 'N')
		img->pa = 3 * PI / 2;
	if (c == 'S')
		img->pa = PI / 2;
	if (c == 'E')
		img->pa = 0;
	if (c == 'W')
		img->pa = PI;
	img->pdx = cos(img->pa) * 3;
	img->pdy = sin(img->pa) * 3;
	free(map_arr);
}
