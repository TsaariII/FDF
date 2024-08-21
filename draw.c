/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/20 15:13:56 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_dots(t_pixel *source, t_pixel *destination, int len)
{
	int	i;
	i = 0;
	while (i < len)
	{
		destination[i] = source[i];
		i++;
	}
}

void	geo_map_shaper(t_fdf *fdf, t_pixel *dots)
{
	scale_z(dots, &fdf->map);
	rotate_x(dots, dots, X_ANGLE, fdf->map.len);
	rotate_y(dots, dots, Y_ANGLE, fdf->map.len);
	rotate_z(dots, dots, Z_ANGLE, fdf->map.len);
	scale_dots(dots, fdf->map.scale, fdf->map.len);
	center(dots, fdf->map.origo, fdf->map.len);
}

void	set_start_end(t_pixel *dot, t_fdf *fdf, int line)
{
	int	i;
	int	end_x;
	int	end_y;
	int	width;
	int	height;

	i = 0;
	width = (int)round(fdf->map.dimension.axels[X]);
	height = (int)round(fdf->map.dimension.axels[Y]);
	while (i < width)
	{
		end_x = i + 1;
		if (end_x >= width)
			end_x = width - 1;
		end_y = i + width;
		draw_line(fdf, dot[i], dot[end_x]);
		if (line + 1 < height)
			draw_line(fdf, dot[i], dot[end_x]);
		i++;
	}
}

void	place_pixel(mlx_image_t *image, float x, float y, int32_t colour)
{
	int	pixel;
	int alpha;

	alpha = 0xFF;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	pixel = ((int)round(y) * WIDTH * 4) + ((int)round(x) * 4);
	base_pixel(&image->pixels[pixel], colour, alpha);
}


void	draw_line(t_fdf *fdf, t_pixel start, t_pixel end)
{
	float	step;
	int		n;
	t_pixel	delta;
	t_pixel	dot;

	n = 0;
	delta.axels[X] = end.axels[X] - start.axels[X];
	delta.axels[Y] = end.axels[Y] - start.axels[Y];
	if (delta.axels[X] >= delta.axels[Y])
		step = delta.axels[X];
	else
		step = delta.axels[Y];
	delta.axels[X] = delta.axels[X] / step;
	delta.axels[Y] = delta.axels[Y] / step;
	dot.axels[X] = start.axels[X];
	dot.axels[Y] = start.axels[Y];

	while (n < step)
	{
		mlx_put_pixel(fdf->image, dot.axels[X], dot.axels[Y], dot.colour);
		dot.axels[X] = dot.axels[X] + delta.axels[X];
		dot.axels[Y] = dot.axels[Y] + delta.axels[Y];
		n++;
	}
}

void	connect_dots(t_fdf *fdf, t_pixel *dots)
{
	int	i;

	i = 0;
	fit_it(fdf, dots);
	while (i < fdf->map.len)
	{
		set_start_end(&dots[i], fdf, i / fdf->map.dimension.axels[X]);
		i = i + fdf->map.dimension.axels[X];
	}
}


void	draw_map(t_fdf *fdf, t_pixel *dots)
{
	copy_dots(fdf->map.dots_array, dots, fdf->map.len);
	geo_map_shaper(fdf, dots);
	background(fdf, fdf->map.colour.background);
	connect_dots(fdf, dots);
}
