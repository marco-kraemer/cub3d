/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:32:09 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_sprites_visible(t_data *img, int numSprites
		, float sprites[get_width_minmap(*img)*get_height_minmap(*img)][3])
{
	float	angleSpritePlayer;
	t_aux	aux;

	aux.i = 0;
	aux.k = 0;
	img->numVisibleSprites = 0;
	img->visibles = malloc
		(sizeof(int) * get_width_minmap(*img) * get_height_minmap(*img));
	while (aux.i < numSprites)
	{
		angleSpritePlayer = img->pa - sprites[aux.i][1];
		if (angleSpritePlayer > PI)
			angleSpritePlayer -= 2 * PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += 2 * PI;
		angleSpritePlayer =fabs(angleSpritePlayer);
		if (angleSpritePlayer < (FOV_ANGLE / 2) + 0.2)
		{
			img->numVisibleSprites++;
			*(img->visibles + aux.k) = aux.i;
			aux.k++;
		}
		aux.i++;
	}
}

void	make_sprites(t_data img
	, int numSprites
	, int color[4][64][64]
	, float sprites[100000][3])
{
	t_aux	aux;
	int		count;

	sort_sprites(sprites, numSprites);
	find_sprites_visible(&img, numSprites, sprites);
	aux.k = 0;
	count = 0;
	while (count < img.numVisibleSprites)
	{
		img.select = *(img.visibles + count++);
		get_sprite_datas(&img, sprites);
		get_tex_datas(&img);
		draw_sprites(img, sprites, color);
	}
	free(img.visibles);
}

void	sprite_data2(t_data img
	, float sprites[100000][3]
	, t_aux *aux)
{
	if (*(img.map_2d + aux->i + aux->j * get_width_minmap(img)) == '2')
	{
		sprites[aux->k][0] = sqrt(((img.px
						- (aux->coordX + 12.5))
					* (img.px - (aux->coordX + 12.5)))
				+ ((img.py - (aux->coordY + 12.5)) * (img.py
						- (aux->coordY + 12.5))));
		sprites[aux->k][1] = 2 * PI
			- (atan2(img.py - (aux->coordY + 12.5),
					(aux->coordX + 12.5) - img.px));
		if (sprites[aux->k][1] < 2 * PI)
			sprites[aux->k][1] += 2 * PI;
		if (sprites[aux->k][1] > 2 * PI)
			sprites[aux->k][1] -= 2 * PI;
		aux->k++;
	}
}

int	sprite_data(t_data img
	, float sprites[100000][3])
{
	t_aux	aux;

	aux.coordY = 0;
	aux.k = 0;
	aux.j = 0;
	while (aux.j < get_height_minmap(img))
	{
		aux.i = 0;
		aux.coordX = 0;
		while (aux.i < get_width_minmap(img))
		{
			sprite_data2(img, sprites, &aux);
			aux.i++;
			aux.coordX += 25;
			if (aux.k > 100000)
			{
				printf("MAXIMUN NUMBER OF SPRITES: 100000\n");
				close_win(&img);
			}
		}
		aux.j++;
		aux.coordY += 25;
	}
	return (aux.k);
}

void	sprites(t_data img, int color[4][64][64])
{
	float	sprites[100000][3];
	int		numSprites;

	numSprites = sprite_data(img, sprites);
	make_sprites(img, numSprites, color, sprites);
}
