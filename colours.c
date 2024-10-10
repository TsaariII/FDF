/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:17:48 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_dots(t_map *map, int i)
{
	while (i < map->len)
	{
		map->dots[i].col = WHITE;
		if (map->dots[i].col_hex > 0)
			map->dots[i].col = map->dots[i].col_hex;
		else if (map->dim.axis[Z] < 0.05)
			map->dots[i].col = map->col.base;
		else if (map->dots[i].axis[Z] == map->dim.axis[Z])
			map->dots[i].col = map->col.top;
		else if (map->dots[i].axis[Z] < 0.05 && map->dots[i].axis[Z] > -0.05)
			map->dots[i].col = map->col.base;
		else if (map->dots[i].axis[Z] == map->min_z && map->min_z != 0)
			map->dots[i].col = map->col.base;
		else if (map->dots[i].axis[Z] == map->min_z && map->min_z != 0)
			map->dots[i].col = map->col.bottom;
		else if (map->dots[i].axis[Z] > 0)
			map->dots[i].col = gradient(map->col.base, map->col.top,
					(int)map->dim.axis[Z], map->dots[i].axis[Z]);
		else
			map->dots[i].col = gradient(map->col.bottom, map->col.base,
					-map->min_z, (map->min_z - map->dots[i].axis[Z]));
		i++;
	}
}

int32_t	gradient(int colour_s, int colour_e, int len, int dot)
{
	float	ratio;
	int		red;
	int		green;
	int		blue;

	if (len == 0)
		return (colour_s);
	ratio = (float)dot / (float)len;
	red = ((1 - ratio) * ((colour_s >> 16) & 0xFF))
		+ (ratio * ((colour_e >> 16) & 0xFF));
	green = ((1 - ratio) * ((colour_s >> 8) & 0xFF))
		+ (ratio * ((colour_e >> 8) & 0xFF));
	blue = ((1 - ratio) * (colour_s & 0xFF)) + (ratio * (colour_e & 0xFF));
	return ((red << 16) + (green << 8) + blue);
}

void	background(t_fdf *fdf, __int32_t background)
{
	int	pixel;
	int	grid[2];
	int	alpha;

	alpha = 0xFF;
	grid[X] = 0;
	grid[Y] = 0;
	while (grid[Y] < HEIGHT)
	{
		while (grid[X] < WIDTH)
		{
			pixel = (grid[Y] * (fdf->image->width * 4)) + (grid[X] * 4);
			base_pixel(&fdf->image->pixels[pixel], background, alpha);
			grid[X]++;
		}
		grid[Y]++;
		grid[X] = 0;
	}
}

int32_t	paint_hexcolour(char *str)
{
	int32_t	colour;

	while (*str != ',')
		str++;
	colour = ft_atoi_base(str + 3, 16);
	return (colour);
}

int	little_big_endian(void)
{
	int		endian;
	int16_t	x;

	x = 0x0001;
	endian = (*((int8_t *)(&x)) == 0x01);
	return (endian);
}
