/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:08:56 by maraurel          #+#    #+#             */
/*   Updated: 2021/05/02 18:12:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, int x, int y)
{
	char	*dst;
	int		ret;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	ret = *(unsigned int *) dst;
	return (ret);
}

int	rgb(int r, int g, int b)
{
	int		c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}
