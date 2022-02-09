/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sky_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:28:10 by maraurel          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:41 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_sky_color2(t_aux aux, char *file, char *color[3], int count)
{
	aux.k = 0;
	while (aux.k < 3)
	{
		aux.j = 0;
		while (file[aux.i] != ',' && file[aux.i] != '\n')
			color[aux.k][aux.j++] = file[aux.i++];
		if (file[aux.i] == '\n' || (file[aux.i] == ','
				&& ft_isdigit(file[aux.i + 1]) == 0))
			break ;
		color[aux.k][aux.j++] = '\0';
		aux.i++;
		aux.k++;
	}
	aux.i = ft_atoi(color[count]);
	aux.j = 0;
	while (aux.j <= 2)
		free(color[aux.j++]);
	if (aux.i < 0 || aux.i > 255 || aux.k != 2)
	{
		printf("Invalid ceiling color!\n");
		exit (0);
	}
	return (aux.i);
}

int	get_sky_color(char *file, int count)
{
	t_aux	aux;
	char	*color[3];

	aux.k = 0;
	while (aux.k < 3)
		color[aux.k++] = malloc(3);
	aux.i = 0;
	while ((file[aux.i] != 'C' || file[aux.i + 1] != ' ') && file[aux.i] != '\0')
		aux.i++;
	if (file[aux.i] == '\0')
	{
		printf("Missing color\n");
		exit (1);
	}
	aux.i++;
	while (file[aux.i] == ' ')
		aux.i++;
	return (get_sky_color2(aux, file, color, count));
}

int	get_floor_color2(t_aux aux, char *file, char *color[3], int count)
{
	aux.k = 0;
	while (aux.k < 3)
	{
		aux.j = 0;
		while (file[aux.i] != ',' && file[aux.i] != '\n')
			color[aux.k][aux.j++] = file[aux.i++];
		if (file[aux.i] == '\n' || (file[aux.i] == ','
				&& ft_isdigit(file[aux.i + 1]) == 0))
			break ;
		color[aux.k][aux.j++] = '\0';
		aux.i++;
		aux.k++;
	}
	aux.i = ft_atoi(color[count]);
	aux.j = 0;
	while (aux.j <= 2)
		free(color[aux.j++]);
	if (aux.i < 0 || aux.i > 255 || aux.k != 2)
	{
		printf("Invalid floor color!\n");
		exit (0);
	}
	return (aux.i);
}

int	get_floor_color(char *file, int count)
{
	t_aux	aux;
	char	*color[3];

	aux.k = 0;
	while (aux.k < 3)
		color[aux.k++] = malloc(3);
	aux.i = 0;
	while ((file[aux.i] != 'F' || file[aux.i + 1] != ' ') && file[aux.i] != '\0')
		aux.i++;
	if (file[aux.i] == '\0')
	{
		printf("Missing color\n");
		exit (1);
	}
	aux.i++;
	while (file[aux.i] == ' ')
		aux.i++;
	return (get_floor_color2(aux, file, color, count));
}
