/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/19 15:25:49 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void place_dot(mlx_image_t *image, float x, float y, int32_t colour)
{
	int dot;
	int alpha;
	alpha = 0xFF;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dot = ((int)round(y) * WIDTH * 4) + ((int)round(x) * 4);
	base_pixel(&image->pixels[dot], colour, alpha);
}

static void	draw_line(t_fdf *fdf, t_dot point0, t_dot point1)
{
	t_dot delta;
	t_dot dot;
	int line;
	int len;

	delta.axels[X] = point1.axels[X] - point0.axels[X];
	delta.axels[Y] = point1.axels[Y] - point0.axels[Y];
	line = sqrt((delta.axels[X] * delta.axels[X]) + (delta.axels[Y] * delta.axels[Y]));
	len = line;
	delta.axels[X] /= line;
	delta.axels[Y] /= line;
	dot.axels[X] = point0.axels[X];
	dot.axels[Y] = point0.axels[Y];
	while (line > 0)
	{
		if (point0.axels[Z] == point1.axels[Z])
			dot.colour = point0.colour;
		else
			dot.colour = gradient(point0.colour, point1.colour, len, len - line);
		place_dot(fdf->image, dot.axels[X], dot.axels[Y], dot.colour);
		dot.axels[X] += delta.axels[X];
		dot.axels[Y] += delta.axels[Y];
		line -= 1;
	}
}

void	draw_map(t_fdf *fdf, t_dot *dots)
{
	int x;
	int y;
	int width;
	int height;

	x = 0;
	y = 0;
	width = fdf->map.dimension.axels[X];
	height = fdf->map.dimension.axels[Y];
	while (y < height)
	{
		x = 0;
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
