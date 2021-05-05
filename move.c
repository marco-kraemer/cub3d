/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:37:48 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 15:19:55 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_move(t_data img)
{
	int	placeX;
	int	placeY;

	placeX = img.px / img.map_width;
	placeY = img.py / img.map_height;
	if (*(img.map_2d + placeX + placeY * get_width_minmap(img)) == '1'
		|| *(img.map_2d + placeX + placeY * get_width_minmap(img)) == '2')
		return (1);
	return (0);
}

int	move_rotation(t_data *img)
{
	if (img->w == 1)
	{
		img->px += img->pdx;
		img->py += img->pdy;
		if (check_move(*img) == 1)
		{
			img->px -= img->pdx;
			img->py -= img->pdy;
		}
	}
	else if (img->s == 1)
	{
		img->px -= img->pdx;
		img->py -= img->pdy;
		if (check_move(*img) == 1)
		{
			img->px += img->pdx;
			img->py += img->pdy;
		}
	}
	return (1);
}

int	move_right_left(t_data *img, int move)
{
	if (img->a == 1)
	{
		img->px += sin(img->pa) * move;
		img->py -= cos(img->pa) * move;
		if (check_move(*img) == 1)
		{
			img->px -= sin(img->pa) * move;
			img->py += cos(img->pa) * move;
		}
	}
	else if (img->d == 1)
	{
		img->px -= sin(img->pa) * move;
		img->py += cos(img->pa) * move;
		if (check_move(*img) == 1)
		{
			img->px += sin(img->pa) * move;
			img->py -= cos(img->pa) * move;
		}
	}
	return (1);
}

int	move_front_back(t_data *img, int move)
{
	if (img->right == 1)
	{
		img->pa -= 0.03;
		if (img->pa < 0)
			img->pa += 2 * PI;
		img->pdx = cos(img->pa) * move;
		img->pdy = sin(img->pa) * move;
	}
	else if (img->left == 1)
	{
		img->pa += 0.03;
		if (img->pa > 2 * PI)
			img->pa -= 2 * PI;
		img->pdx = cos(img->pa) * move;
		img->pdy = sin(img->pa) * move;
	}
	return (1);
}

int	key_press(int keycode, t_data *img)
{
	if (keycode == 119)
		img->w = 1;
	if (keycode == 97)
		img->a = 1;
	if (keycode == 115)
		img->s = 1;
	if (keycode == 100)
		img->d = 1;
	if (keycode == 65361)
		img->right = 1;
	if (keycode == 65363)
		img->left = 1;
	if (keycode == 65307)
		img->esc = 1;
	return (0);
}

int	move_player(t_data *img)
{
	int		move;

	move = 3;
	if (img->esc == 1)
		close_win(img);
	move_front_back(img, move);
	move_right_left(img, move);
	move_rotation(img);
	print_images(img);
	return (0);
}
