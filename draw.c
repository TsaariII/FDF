/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:27:54 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/25 16:21:20 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int compute_outcode(mlx_image_t *img, t_dot *dot)
{
	int code;

	code = INSIDE;
	if (dot->axels[X] < 1)
		code |= LEFT;
	if (dot->axels[X] > (int)(img->width - 1))
		code |= RIGHT;
	if (dot->axels[Y] < 1)
		code |= TOP;
	if (dot->axels[Y] > (int)(img->height - 1))
		code |= BOTTOM;
	return (code);
}

static void	update_xy(mlx_image_t *img, int *xy, int *out, t_dot *dot)
{
	dot->axels[X] = xy[0];
	dot->axels[Y] = xy[1];
	*out = compute_outcode(img, dot);
}

static int jack_bauer(mlx_image_t *img, int out[2], t_dot *s, t_dot *e)
{
	int update;
	int xy[2];

	while ((out[0] | out[1]))
	{
		if (out[0] & out[1])
			return (0);
		if (out[0] > out[1])
			update = out[0];
		else
			update = out[1];
		if (update & BOTTOM)
			clip_bottom(img, s, e, xy);
		else if (update & TOP)
			clip_top(s, e, xy);
		else if (update & RIGHT)
			clip_right(img, s, e, xy);
		else if (update & LEFT)
			clip_left(s, e, xy);
		if (update == out[0])
			update_xy(img, xy, &out[0], s);
		else
			update_xy(img, xy, &out[1], e);
	}
	return (1);
}

int clip_line(mlx_image_t *img, t_dot *s, t_dot *e)
{
	int out[2];
	int res;
	out[0] = compute_outcode(img, s);
	out[1] = compute_outcode(img, e);
	res = jack_bauer(img, out, s, e);
	return (res);
}

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
		if (!clip_line(fdf->image, &point0, &point1))
			break ;
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
