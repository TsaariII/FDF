/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/21 17:07:28 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void	copy_dots(t_pixel *source, t_pixel *dest, int len)
{
	int	n;

	n = 0;
	while (n < len)
	{
		dest[n] = source[n];
		n++;
	}
}

void	center(t_pixel *dots, t_pixel origo, int len)
{
	int	n;

	n = 0;
	while (n < len)
	{
		dots[n].axels[X] = dots[n].axels[X] + origo.axels[X];
		dots[n].axels[Y] = dots[n].axels[Y] + origo.axels[Y];
		dots[n].axels[Z] = dots[n].axels[Z] + origo.axels[Z];
		n++;
	}
}


static void x_y_line(t_pixel *dot, t_fdf *fdf, int current)
{
	int i;
	int e_x;
	int e_y;
	int width;
	int height;

	i = 0;
	width = (int)round(fdf->map.dimension.axels[X]);
	height = (int)round(fdf->map.dimension.axels[Y]);
	while (i < width)
	{
		e_x = i + 1;
		if (e_x >= width)
			e_x = width + 1;
		e_y = i + width;
		line(fdf, dot[i], dot[e_x]);
		if (current + 1 < height)
			line(fdf, dot[i], dot[e_y]);
		i++;
	}
}

void draw_lines(t_fdf *fdf, t_pixel *dots)
{
	int	i;

	i = 0;
	fit_it(fdf, dots);
	while (i < fdf->map.len)
	{
		x_y_line(&dots[i],fdf, i / fdf->map.dimension.axels[X]);
		i = i + fdf->map.dimension.axels[X];
	}
}


void	place_dot(mlx_image_t *image, float x, float y, int32_t colour)
{
	int dot;
	int alpha;
	alpha = 0xFF;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dot = ((int)round(y) * WIDTH * 4) + ((int)round(x) * 4);
	base_pixel(&image->pixels[dot], colour, alpha);
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

void	draw_map(t_fdf *fdf, t_pixel *dots)
{
	copy_dots(fdf->map.dots_array, dots, fdf->map.len);
	geo_map_shaper(fdf, dots);
	background(fdf, fdf->map.colour.background);
	draw_lines(fdf, dots);
}
