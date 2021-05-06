/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 22:37:18 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/05 22:51:43 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
