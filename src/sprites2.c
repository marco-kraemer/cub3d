/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:53:32 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sort_sprites(float sprites[100000][3], int numSprites)
{
	t_aux	aux;
	float	temp;

	aux.i = 0;
	aux.j = 0;
	while (aux.i < numSprites - 1)
	{
		aux.j = aux.i + 1;
		while (aux.j < numSprites)
		{
			if (sprites[aux.i][0] < sprites[aux.j][0])
			{
				temp = sprites[aux.i][0];
				sprites[aux.i][0] = sprites[aux.j][0];
				sprites[aux.j][0] = temp;
				temp = sprites[aux.i][1];
				sprites[aux.i][1] = sprites[aux.j][1];
				sprites[aux.j][1] = temp;
			}
			aux.j++;
		}
		aux.i++;
	}
}

void	get_sprite_datas(t_data *img
		, float sprites[get_width_minmap(*img)*get_height_minmap(*img)][3])
{
	img->perpDistance = sprites[img->select][0];
	img->spriteHeight = (1080 / img->perpDistance) * 20;
	img->spriteWidth = img->spriteHeight;
	img->spriteTopY = (img->height / 2) - (img->spriteHeight / 2);
	if (img->spriteTopY < 0)
		img->spriteTopY = 0;
	img->spriteBottomY = (img->height / 2) + (img->spriteHeight / 2);
	if (img->spriteBottomY > img->height)
		img->spriteBottomY = img->height;
	img->spriteAngle = sprites[img->select][1] - img->pa;
	img->spriteScreenPosX = tan(img->spriteAngle) * 1000;
	img->spriteLeftX = (img->width / 2)
		+ img->spriteScreenPosX - (img->spriteWidth / 2);
	img->spriteRightX = img->spriteLeftX + img->spriteWidth;
}

void	get_tex_datas(t_data *img)
{
	img->texStep = img->spriteHeight / 64;
	img->spriteTexX = 0;
	img->first_pixel = 0;
	if (img->spriteHeight > img->height)
	{
		img->first_pixel = img->spriteHeight - img->height;
		img->first_pixel = img->first_pixel / 2;
		img->spriteHeight = img->height;
	}
	img->check_tex_width = (img->width - 1048) / 2;
	if (img->check_tex_width < 0)
		img->check_tex_width = 0;
}

void	draw_sprites2(t_data img
	, float sprites[100000][3]
	, int color[4][64][64], t_aux aux)
{
	if (aux.j + img.spriteLeftX > img.check_tex_width)
	{
		img.spriteTexY = 0;
		while (aux.k < img.first_pixel)
		{
			aux.k += img.texStep;
			img.spriteTexY++;
		}
		aux.k = 0;
		aux.m = 1;
		while (img.spriteTopY + aux.k < img.spriteBottomY)
		{
			if (color[4][img.spriteTexX][img.spriteTexY] != 0x000000
				&& sprites[img.select][0] < img.zBuffer[(int)(aux.j
					+ img.spriteLeftX - img.check_tex_width)])
				my_mlx_pixel_put(&img, aux.j + img.spriteLeftX, img.spriteTopY
					+ aux.k, color[4][img.spriteTexX][img.spriteTexY]);
			aux.k++;
			while (aux.k >= img.texStep * aux.m)
			{
				img.spriteTexY++;
				aux.m++;
			}
		}
	}
}

void	draw_sprites(t_data img
	, float sprites[100000][3]
	, int color[4][64][64])
{
	int		m;
	t_aux	aux;

	m = 0;
	aux.j = 0;
	aux.k = 0;
	if (aux.j + img.spriteLeftX < img.width - img.check_tex_width)
	{
		while (aux.j + img.spriteLeftX < img.spriteRightX
			&& aux.j + img.spriteLeftX < img.width - img.check_tex_width)
		{
			draw_sprites2(img, sprites, color, aux);
			aux.j++;
			while (aux.j >= img.texStep * m && img.spriteTexX < 63)
			{
				img.spriteTexX++;
				m++;
			}
		}
	}
	img.select++;
}
