/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:28:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 15:05:05 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_height_minmap(t_data img)
{
	int		num_lines;
	int		i;

	num_lines = 1;
	i = 0;
	while (img.map[i + 1] != '\0')
	{
		if (img.map[i] == '\n')
			num_lines++;
		i++;
	}
	return (num_lines);
}	

int	get_width_minmap(t_data img)
{
	int		num_columns;
	int		old;
	int		i;

	num_columns = 0;
	old = 0;
	i = 0;
	while (img.map[i] != '\0')
	{
		num_columns++;
		i++;
		if ((img.map[i] == '\n') && num_columns > old)
			old = num_columns;
		if (img.map[i] == '\n')
			num_columns = 0;
	}
	if (old > num_columns)
		return (old - 1);
	return (num_columns - 1);
}

int	check_argv(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (arg[0] == '-' && arg[1] == '-' && arg[2] == 's'
		&& arg[3] == 'a' && arg[4] == 'v'
		&& arg[5] == 'e' && i == 6)
		return (1);
	return (0);
}

int	check_argv2(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '.'
			&& arg[i + 1] == 'c'
			&& arg[i + 2] == 'u'
			&& arg[i + 3] == 'b'
			&& arg[i + 4] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	key_release(int keycode, t_data *img)
{
	if (keycode == 119)
		img->w = 0;
	if (keycode == 97)
		img->a = 0;
	if (keycode == 115)
		img->s = 0;
	if (keycode == 100)
		img->d = 0;
	if (keycode == 65361)
		img->right = 0;
	if (keycode == 65363)
		img->left = 0;
	return (0);
}
