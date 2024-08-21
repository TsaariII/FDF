/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/21 17:09:29 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (multiplied);
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

void	scale_z(t_pixel *dots, t_map *map)
{
	float	ratio;
	int		divider;
	int		i;

	i = 0;
	divider = 1;
	ratio = map->dimension.axels[Z] / map->dimension.axels[X];
	if (ratio > 0.5)
		divider = ratio * Z_SCALE;
	while (i < map->len)
	{
		dots[i].axels[Z] = dots[i].axels[Z] / divider;
		i++;
	}
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


void	line(t_fdf *fdf, t_pixel start, t_pixel end)
{
	t_pixel	delta;
	t_pixel	dot;
	int		line;
	int		len;
	if (!valid_dot(&start) && !valid_dot(&end))
		return ;
	delta.axels[X] = end.axels[X] - start.axels[X];
	delta.axels[Y] = end.axels[Y] - start.axels[Y];
	line = sqrt((delta.axels[X] * delta.axels[X])
				+ (delta.axels[Y] * delta.axels[Y]));
	len = line;
	delta.axels[X] /= line;
	delta.axels[Y] /= line;
	dot.axels[X] = start.axels[X];
	dot.axels[Y] = start.axels[Y];
	while (line > 0)
	{
		dot.colour = gradient(start.colour, end.colour, len, len - line);
		place_dot(fdf->image, dot.axels[X], dot.axels[Y], dot.colour);
		dot.axels[X] += delta.axels[X];
		dot.axels[Y] += delta.axels[Y];
		line -= 1;
	}
}
