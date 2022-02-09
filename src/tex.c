/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:11:54 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	tex_to_array(t_data *img, int color[5][64][64],
			int tex_width, int tex_height)
{
	t_aux	aux;

	aux.k = 0;
	while (aux.k < 5)
	{
		img->addr = mlx_get_data_addr
			(img->tex[aux.k], &img->bits_per_pixel,
				&img->line_length, &img->endian);
		aux.i = 0;
		while (aux.i < tex_height)
		{
			aux.j = 0;
			while (aux.j < tex_width)
			{
				color[aux.k][aux.i][aux.j] = get_color(img, aux.i, aux.j);
				aux.j++;
			}
			aux.i++;
		}
		mlx_destroy_image(img->mlx, img->tex[aux.k]);
		aux.k++;
	}
}

void	get_textures(t_data *img, int color[5][64][64])
{
	t_aux	aux;
	int		tex_width;
	int		tex_height;

	aux. i = 0;
	while (aux.i < 5)
	{
		img->tex[aux.i] = mlx_xpm_file_to_image
			(img->mlx, img->path_to_tex[aux.i], &tex_width, &tex_height);
		free(img->path_to_tex[aux.i]);
		if (img->tex[aux.i] == NULL)
		{
			printf("Invalid texture path\n");
			exit(1);
		}
		aux.i++;
	}
	tex_to_array(img, color, tex_width, tex_height);
}

int	get_tex_path2(char *file, int count)
{
	int		i;

	i = 0;
	if (count == 2)
		while ((file[i] != 'N' || file[i + 1] != 'O') && file[i] != '\0')
			i++;
	else if (count == 3)
		while ((file[i] != 'S' || file[i + 1] != 'O') && file[i] != '\0')
			i++;
	else if (count == 1)
		while ((file[i] != 'W' || file[i + 1] != 'E') && file[i] != '\0')
			i++;
	else if (count == 0)
		while ((file[i] != 'E' || file[i + 1] != 'A') && file[i] != '\0')
			i++;
	else if (count == 4)
	{
		while ((file[i] != 'S' || file[i + 1] != ' ') && file[i] != '\0')
			i++;
		i--;
	}
	i += 2;
	while (file[i + 1] == ' ')
		i++;
	return (i);
}

char	*get_tex_path(char *file, int count)
{
	int		i;
	int		j;
	char	*path;

	j = 0;
	i = get_tex_path2(file, count);
	if (i >= (int)ft_strlen(file))
	{
		printf("Missing texture path\n");
		exit (0);
	}
	j = 0;
	while (file[i + j] != '\n')
		j++;
	i++;
	path = malloc(sizeof(char) * j);
	j = 0;
	while (file[i] != '\n')
		path[j++] = file[i++];
	if (path == NULL)
	{
		printf("ERROR\n");
		exit (0);
	}
	return (path);
}
