/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:27:59 by maraurel          #+#    #+#             */
/*   Updated: 2021/04/30 09:56:15 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bdata(t_data *img, int fd)
{
	int		i;
	int		j;
	int		color;

	i = img->height;
	color = 0;
	while (i > 0)
	{
		j = 0;
		while (j < img->width)
		{
			color = get_color(img, j, i);
			write(fd, &color, 4);
			j++;
		}
		i--;
	}
}

void	ft_binfo(t_data *img, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = img->width;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = img->height;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	ft_bfile(t_data *img, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = img->width * img->height * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int	bitmap(t_data *img)
{
	int		fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_bfile(img, fd);
	ft_binfo(img, fd);
	ft_bdata(img, fd);
	close(fd);
	return (1);
}
