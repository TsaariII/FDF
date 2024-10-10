/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	place_dot(mlx_image_t *image, float x, float y, int32_t colour)
{
	int	dot;
	int	alpha;

	alpha = 0xFF;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dot = ((int)round(y) * WIDTH * 4) + ((int)round(x) * 4);
	base_pixel(&image->pixels[dot], colour, alpha);
}

static void	draw_line(t_fdf *fdf, t_dot point0, t_dot point1)
{
	t_dot	delta;
	t_dot	dot;
	int		line;
	int		len;

	if (!clip_line(fdf->image, &point0, &point1))
		return ;
	delta.axis[X] = point1.axis[X] - point0.axis[X];
	delta.axis[Y] = point1.axis[Y] - point0.axis[Y];
	line = sqrt((delta.axis[X] * delta.axis[X])
			+ (delta.axis[Y] * delta.axis[Y]));
	len = line;
	delta.axis[X] /= line;
	delta.axis[Y] /= line;
	dot.axis[X] = point0.axis[X];
	dot.axis[Y] = point0.axis[Y];
	while (line > 0)
	{
		dot.col = gradient(point0.col, point1.col, len, len - line);
		place_dot(fdf->image, dot.axis[X], dot.axis[Y], dot.col);
		dot.axis[X] += delta.axis[X];
		dot.axis[Y] += delta.axis[Y];
		line -= 1;
	}
}

void	draw_map(t_fdf *fdf, t_dot *dots)
{
	int	x;
	int	y;
	int	width;
	int	height;

	x = 0;
	y = 0;
	width = fdf->map.dim.axis[X];
	height = fdf->map.dim.axis[Y];
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
