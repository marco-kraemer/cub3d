/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:04 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_file(t_data *img, char *argv[])
{
	int		i;
	int		fd;
	char	buf;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || check_argv2(argv[1]) == 1)
	{
		printf("Invalid file name\n");
		exit (0);
	}
	while (read(fd, &buf, 1) != 0)
		i++;
	img->file = malloc(i + 1 * sizeof(char));
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, img->file, i) < 0)
	{
		free(img->file);
		printf("ERROR\n");
		exit (0);
	}
	img->file[i] = '\0';
	close(fd);
}

int	get_res_width(t_data img)
{
	int		i;
	int		j;
	char	*width;

	i = 0;
	while (img.file[i] != 'R')
		i++;
	i++;
	while (img.file[i] == ' ')
		i++;
	j = 0;
	while (img.file[i + j] != ' ')
		j++;
	width = malloc(sizeof(char) * j);
	j = 0;
	while (img.file[i] != ' ')
		width[j++] = img.file[i++];
	i = ft_atoi(width);
	free(width);
	if (i > 1920)
		return (1920);
	return (i);
}

int	get_res_height(t_data img)
{
	int		i;
	int		j;
	char	*height;

	i = 0;
	while (img.file[i] != 'R' && img.file[i] != '\0')
		i++;
	if (img.file[i] == '\0')
		close_map_error(&img, 3);
	i += 2;
	while (img.file[i] != ' ')
		i++;
	i++;
	j = 0;
	while (img.file[i + j] == ' ')
		j++;
	height = malloc(sizeof(char) * (j - 0));
	j = 0;
	while (img.file[i] != ' ')
		height[j++] = img.file[i++];
	i = ft_atoi(height);
	free(height);
	if (i > 1080)
		return (1080);
	return (i);
}
