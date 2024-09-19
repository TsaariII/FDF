/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:17:48 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/19 15:29:31 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_dots(t_map *map, t_dot *dots, t_colours colours)
{
	int	i;
	int z;

	i = 0;
	z = map->dimension.axels[Z] - map->min_z;
	while (i < map->len)
	{
		dots[i].colour = YELLOW;
		if (dots[i].colour_hex > 0)
			dots[i].colour = dots[i].colour_hex;
		else if (dots[i].axels[Z] == map->dimension.axels[Z])
			dots[i].colour = colours.top;
		else if (dots[i].axels[Z] == 0)
			dots[i].colour = colours.base;
		else if (dots[i].axels[Z] == map->min_z && map->min_z != 0)
			dots[i].colour = colours.bottom;
		// else if (dots[i].axels[Z] > 0)
		// 	dots[i].colour = gradient(colours.base, colours.top, (int)map->dimension.axels[Z], dots[i].axels[Z]);
		// else
		// 	dots[i].colour = gradient(colours.bottom, colours.base, - map->min_z, - (map->min_z - dots[i].axels[Z]));
		i++;
	}
}

int32_t	gradient(int colour_s, int colour_e, int len, int dot)
{
	float	rgb[3];
	int		new[3];
	int		dot_colour;

	rgb[RED] = (float)((colour_e >> 16) - (colour_s >> 16)) / (float)len;
	rgb[GREEN] = (float)((colour_e >> 8) & 0xFF) - ((colour_s >> 8 & 0xFF)) / (float)len;
	rgb[BLUE] = (float)((colour_e & 0xFF) - (colour_s & 0xFF)) / (float)len;
	new[RED] = ((colour_s >> 16) & 0xFF) + (int)round(dot * rgb[RED]);
	new[GREEN] = ((colour_s >> 8) & 0xFF) + (int)round(dot * rgb[GREEN]);
	new[BLUE] = (colour_s & 0xFF) + (int)round(dot * rgb[BLUE]);
	dot_colour = (new[RED] << 16) + (new[GREEN] << 8) + new[BLUE];
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
	while (grid[Y] < HEIGHT)
	{
		while (grid[X] < WIDTH)
		{
			pixel = (grid[Y] * (fdf->image->width *4)) + (grid[X] * 4);
			base_pixel(&fdf->image->pixels[pixel], background, alpha);
			grid[X]++;
		}
		grid[Y]++;
		grid[X] = 0;
	}
}

int32_t	paint_hexcolour(char *str)
{
	int32_t colour;

	while (*str != ',')
		str++;
	colour = ft_atoi_base(str + 3, 16);
	return (colour);
}
