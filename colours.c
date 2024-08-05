/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:17:48 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/05 14:06:36 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dot_colours(t_map *map, t_pixel *dots, t_colours colours)
{
	int	i;
	int z;

	i = 0;
	z = map->dimension.axels[Z] - map->min_z;
	while (i < map->len)
	{
		dots[i].colours = BLACK;
		if (dots[i].hex_colour > 0)
			dots[i].colour = dots[i].hex_colour;
		else if (dots[i].axels[Z] == map->dimension.axels[Z])
			dots[i].colour = colours.top;
		else if (dots[i].axels[Z] == 0)
			dots[i].colour = colours.base;
		else if (dots[i].axels[Z] == map->min_z && map->min_z != 0)
			dots[i].colour = colours.bottom;
		else if (dots[i].axels[Z] > 0)
			dots.colour = gradient(colours.base, colours.top, (int)map->dimension.axels[Z], dots[i].axels[Z]);
		else
			dots[i].colour = gradient(colours.bottom, colours.base, - map->min_z, - (map->min_z - dots[i].axis[Z]));
		i++
	}
}

int32_t	gradient(int colour_s, int colour_e, int len, int dot)
{
	float	rgb[3];
	int		new[3];
	int		dot_colour;

	rgb[R] = (float)((colour_e >> 16) - (colour_s >> 16)) / (float)len;
	rgb[G] = (float)((colour_e >> 8) & 0xFF) - ((colour_s >> 8 & 0xFF)) / (float)len;
	rgb[B] = (float)((colour_e & 0xFF) - (colour_s & 0xFF)) / (float)len;
	new[R] = ((colour_s >> 16) & 0xFF) + (int)round(dot * rgb[R]);
	new[G] = ((colour_s >> 8) & 0xFF) + (int)round(dot * rgb[G]);
	new[B] = (colour_s & 0xFF) + (int)round(dot * rgb[B]);
	dot_colour = (new[R] << 16) + (new[G] << 8) + new[B];
	return (dot_colour);
}

void	background(t_fdf *fdf, __int32_t background)
{
	int	pixel;
	int	grid[2];
	int alpha;

	alpha = 0xFF;
	grid[X] = 0;
	grid[Y] = 0;
	while (grid[Y] < WIN_Y)
	{
		while (grid[X] < WIN_X)
		{
			pixel = (grid[Y] * (fdf->image->width *4)) + (grid[X] * 4);
			base_pixel(&fdf->image->pixels[pixel], background, alpha);
			grid[X]++;
		}
		grid[Y]++;
		grid[X] = 0;
	}
}
