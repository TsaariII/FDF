/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 10:28:20 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(t_fdf *fdf, int x, int y, int colour)
{
	char *dot;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dot = (char *)fdf->image->pixels + (y * fdf->image->width * 4 + x * 4);
		*(unsigned int *)dot = colour;
		dot = (char *)fdf->image->pixels + (y * fdf->image->width * 4 + x * 4);
		*(unsigned int *)dot = colour;
	}
}

static void	draw_line(t_fdf *fdf, t_pixel point0, t_pixel point1)
{
	float step;
	float x;
	float y;
	int i;
	t_pixel delta;

	delta.axels[X] = point1.axels[X] - point0.axels[X];
	delta.axels[Y] = point1.axels[Y] - point0.axels[Y];
	delta.axels[X] = point1.axels[X] - point0.axels[X];
	delta.axels[Y] = point1.axels[Y] - point0.axels[Y];
	if (fabsf(delta.axels[X]) >= fabsf(delta.axels[Y]))
		step = fabsf(delta.axels[X]);
	else
		step = fabsf(delta.axels[Y]);
	delta.axels[X] /= step;
	delta.axels[Y] /= step;
	x = point0.axels[X];
	y = point0.axels[Y];
	i = 0;
	while (i < step)
	{
		put_pixel(fdf, (int)round(x), (int)round(y), point0.colour);
		x += delta.axels[X];
		y += delta.axels[Y];
		i++;
	}
}

void	draw_map(t_fdf *fdf, t_pixel *dots)
{
	int x;
	int y;
	int width;
	int height;

	x = 0;
	y = 0;
	width = fdf->map.dimension.axels[X];
	height = fdf->map.dimension.axels[Y];

	x = 0;
	y = 0;
	width = fdf->map.dimension.axels[X];
	height = fdf->map.dimension.axels[Y];
	while (y < height)
	{
		while (x < width)
		{
			if (x < width - 1)
				draw_line(fdf, dots[y * width + x], dots[y * width + (x + 1)]);
			if (y < height - 1)
				draw_line(fdf, dots[y * width + x], dots[(y + 1) * width + x]);
			x++;
		}
		y++;
	}
}
