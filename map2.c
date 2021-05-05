/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:47:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 10:50:34 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map2(t_data *img, t_aux aux, int length)
{
	if ((*(img->map_2d + (aux.i + 1) + (aux.j + 1) * length) != '1'
			&& *(img->map_2d + (aux.i + 1) + (aux.j + 1) * length) != ' '
			&& *(img->map_2d + (aux.i + 1) + (aux.j + 1) * length) != 0)
		|| (*(img->map_2d + (aux.i - 1) + (aux.j - 1) * length) != '1'
			&& *(img->map_2d + (aux.i - 1) + (aux.j - 1) * length) != ' '
			&& *(img->map_2d + (aux.i - 1) + (aux.j - 1) * length) != 0)
		|| (*(img->map_2d + (aux.i - 1) + (aux.j + 1) * length) != '1'
			&& *(img->map_2d + (aux.i - 1) + (aux.j + 1) * length) != ' '
			&& *(img->map_2d + (aux.i - 1) + (aux.j + 1) * length) != 0)
		|| (*(img->map_2d + (aux.i + 1) + (aux.j - 1) * length) != '1'
			&& *(img->map_2d + (aux.i + 1) + (aux.j - 1) * length) != ' '
			&& *(img->map_2d + (aux.i + 1) + (aux.j - 1) * length) != 0))
		return (1);
	return (0);
}

int	check_map(t_data *img, t_aux aux, int length)
{
	if ((*(img->map_2d + (aux.i + 1) + aux.j * length) != '1'
			&& *(img->map_2d + (aux.i + 1) + aux.j * length) != ' '
			&& *(img->map_2d + (aux.i + 1) + aux.j * length) != 0)
		|| (*(img->map_2d + aux.i + (aux.j + 1) * length) != '1'
			&& *(img->map_2d + aux.i + (aux.j + 1) * length) != ' '
			&& *(img->map_2d + aux.i + (aux.j + 1) * length) != 0)
		|| (*(img->map_2d + (aux.i - 1) + aux.j * length) != '1'
			&& *(img->map_2d + (aux.i - 1) + aux.j * length) != ' '
			&& *(img->map_2d + (aux.i - 1) + aux.j * length) != 0)
		|| (*(img->map_2d + aux.i + (aux.j - 1) * length) != '1'
			&& *(img->map_2d + aux.i + (aux.j - 1) * length) != ' '
			&& *(img->map_2d + aux.i + (aux.j - 1) * length) != 0)
		|| check_map2(img, aux, length) == 1)
		return (1);
	return (0);
}

void	parse_map3(t_data *img)
{
	int		length;
	t_aux	aux;

	aux.i = 0;
	aux.j = 1;
	aux.k = 1;
	length = get_width_minmap(*img);
	check_first_line(img, length);
	check_last_line(img, length);
	while (aux.j < get_height_minmap(*img) - 2)
	{
		if (*(img->map_2d + aux.i + aux.j * length) == ' ')
		{
			if (check_map(img, aux, length) == 1)
				close_map_error(img, 2);
		}
		aux.i++;
		if (aux.i == length)
		{
			aux.i = 0;
			aux.j++;
		}
	}
}

void	map_array_2d(t_data *img)
{
	t_aux	aux;

	aux.i = 0;
	aux.j = 0;
	aux.k = 0;
	img->map_2d = malloc(get_width_minmap(*img)
			* get_height_minmap(*img) * sizeof (char));
	while (img->map[aux.k])
	{
		*(img->map_2d + aux.i + aux.j
				* get_width_minmap(*img)) = *(img->map + aux.k);
		aux.i++;
		aux.k++;
		if (img->map[aux.k] == '\n' || img->map[aux.k] == '\0')
		{
			while (aux.i <= get_width_minmap(*img))
				*(img->map_2d + aux.i++ + aux.j * get_width_minmap(*img)) = ' ';
			aux.j++;
			aux.k++;
			aux.i = 0;
		}
	}
	parse_map3(img);
}
