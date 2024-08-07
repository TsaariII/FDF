/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/07 16:23:37 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_z(t_pixel *dots, t_map *map)
{
	float	size;
	int		divisor;
	int 	n;

	n = 0;
	divisor = 1;
	size = map->dimension.axels[Z] / map->dimension.axels[X];
	if (size > 0.5)
		divisor = size * Z_SCALE;
	while (n < map->len)
	{
		dots[n].axels[Z] = dots[n].axels[Z] / divisor;
		n++;
	}
}

void	rotate_x(t_pixel *dots, t_pixel *projection, float angle, int len)
{
	int		y;
	int		x;
	float	radius;
	float	matrix[3][3];

	y = 0;
	radius = angle * M_PI / 180;
	while (y < 3)
	{
		x = 0;
		{
			matrix[y][x] = 0;
			x++;
		}
		y++;
	}
	matrix[0][0] = 1;
	matrix[1][1] = cos(radius);
	matrix[1][2] = -sin(radius);
	matrix[2][1] = sin(radius);
	matrix[2][2] = cos(radius);
	y = -1;
	while (++y < len)
		projection[y] = multiply_matrix(matrix, dots[y]);
}

void	rotate_y(t_pixel *dots, t_pixel *projection, float angle, int len)
{
	int		y;
	int		x;
	float	radius;
	float	matrix[3][3];

	y = 0;
	radius = angle * M_PI / 180;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			matrix[y][x] = 0;
			x++;
		}
		y++;
	}
	matrix[0][0] = cos(radius);
	matrix[0][2] = sin(radius);
	matrix[1][1] = 1;
	matrix[2][0] = -sin(radius);
	matrix[2][2] = cos(radius);
	y = -1;
	while (++y < len)
		projection[y] = multiply_matrix(matrix, dots[y]);
}

void	rotate_z(t_pixel *dots, t_pixel *projection, float angle, int len)
{
	int		y;
	int		x;
	float	radius;
	float	matrix[3][3];

	y = 0;
	radius = angle * M_PI / 180;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			matrix[y][x] = 0;
			x++;
		}
		y++;
	}
	matrix[0][0] = cos(radius);
	matrix[0][1] = -sin(radius);
	matrix[1][0] = sin(radius);
	matrix[1][1] = cos(radius);
	matrix[2][2] = 1;
	y = -1;
	while (++y < len)
		projection[y] = multiply_matrix(matrix, dots[y]);
}

t_pixel	multiply_matrix(float matrix[3][3], t_pixel dot)
{
	int		y;
	int		x;
	t_pixel	multiplied;

	y = 0;
	multiplied = dot;
	while (y < 3)
	{
		multiplied.axels[y] = 0;
		multiplied.colour = dot.colour;
		x = 0;
		while (x < 3)
		{
			multiplied.axels[y] += matrix[y][x] * dot.axels[x];
			x++;
		}
		y++;
	}
	return(multiplied);
}

void	scale_dots(t_pixel *array, float scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		array[i].axels[X] *= scale;
		array[i].axels[Y] *= scale;
		array[i].axels[Z] *= scale;
		i++;
	}
}

void	center(t_pixel *dots, t_pixel origo, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dots[i].axels[X] = dots[i].axels[X] + origo.axels[X];
		dots[i].axels[Y] = dots[i].axels[Y] + origo.axels[Y];
		dots[i].axels[Z] = dots[i].axels[Z] + origo.axels[Z];
		i++;
	}
}
