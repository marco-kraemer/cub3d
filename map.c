/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:46:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 13:58:17 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_first_line(t_data *img, int length)
{
	t_aux	aux;

	aux.i = 0;
	aux.k = get_height_minmap(*img) - 1;
	while (aux.i < length)
	{
		if (*(img->map_2d + aux.i + 0 * length) != '1')
		{
			if ((*(img->map_2d + aux.i + 1 * length) == '0'
					|| *(img->map_2d + aux.i + 1 * length) == '2')
				|| (*(img->map_2d + (aux.i - 1) + 1 * length) == '0'
					|| *(img->map_2d + (aux.i - 1) + 1 * length) == '2')
				|| (*(img->map_2d + (aux.i + 1) + 1 * length) == '0'
					|| *(img->map_2d + (aux.i + 1) + 1 * length) == '2'))
			{
				printf("Invalid map: First line\n");
				exit (0);
			}
		}
		aux.i++;
	}
}

void	check_last_line(t_data *img, int length)
{
	t_aux	aux;

	aux.i = 0;
	aux.k = get_height_minmap(*img) - 1;
	while (aux.i < length)
	{
		if (*(img->map_2d + aux.i + aux.k * length) != '1')
		{
			if ((*(img->map_2d + aux.i + (aux.k - 1) * length) == '0'
					|| *(img->map_2d + aux.i + (aux.k - 1) * length) == '2')
				|| (*(img->map_2d + (aux.i - 1) + (aux.k - 1) * length) == '0'
					|| *(img->map_2d + (aux.i - 1)
						+ (aux.k - 1) * length) == '2')
				|| (*(img->map_2d + (aux.i + 1)
						+ (aux.k - 1) * length) == '0'
					|| *(img->map_2d + (aux.i + 1)
						+ (aux.k - 1) * length) == '2'))
			{
				printf("Invalid map: Last line\n");
				exit (0);
			}
		}
		aux.i++;
	}
}

void	parse_map2(t_data img, char *map)
{
	int	i;

	i = 0;
	while (map[i++] != '\n')
		if (map[i - 1] != ' ' && map[i - 1] != '1')
			close_map_error(&img, 2);
	while (map[i])
	{
		if (map[i] == '\n' && (map[i + 1] != ' ' && map[i + 1] != '1'))
			close_map_error(&img, 2);
		if (map[i] == '\n' && (map[i - 1] != ' ' && map[i - 1] != '1'))
			close_map_error(&img, 2);
		i++;
	}
	i--;
	while (map[i--] != '\n')
		if (map[i + 1] != ' ' && map[i + 1] != '1')
			close_map_error(&img, 2);
}

void	parse_map(t_data img, char *map)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
			player++;
		if (map[i] != 'N' && map[i] != 'S' && map[i] != 'E' && map[i] != 'W'
			&& map[i] != ' ' && map[i] != '1' && map[i] != '2'
			&& map[i] != '\n' && map[i] != '0')
			close_map_error(&img, 1);
		if (map[i] == '\n' && map[i + 1] == '\n')
			close_map_error(&img, 2);
		i++;
	}
	if (player != 1)
		close_map_error(&img, 0);
	parse_map2(img, map);
}

char	*get_map(t_data img, char *file)
{
	int		i;
	int		j;
	char	*map;

	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == '\n' && (ft_isdigit(file[i + 1]) || file[i + 1] == ' '))
		{
			i++;
			break ;
		}
		i++;
	}
	while (file[i++])
		j++;
	map = malloc(j * sizeof(char));
	j = i - j - 1;
	i = 0;
	while (file[j])
		map[i++] = file[j++];
	map[i] = '\0';
	parse_map(img, map);
	return (map);
}
