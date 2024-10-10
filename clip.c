/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:22:57 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	compute_outcode(mlx_image_t *img, t_dot *dot)
{
	int	code;

	code = INSIDE;
	if (dot->axis[X] < 1)
		code |= LEFT;
	if (dot->axis[X] > (img->width - 1))
		code |= RIGHT;
	if (dot->axis[Y] < 1)
		code |= TOP;
	if (dot->axis[Y] > (img->height - 1))
		code |= BOTTOM;
	return (code);
}

static int	jack_bauer(mlx_image_t *img, int out[2], t_dot *s, t_dot *e)
{
	int		update;
	float	xy[2];

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

int	clip_line(mlx_image_t *img, t_dot *s, t_dot *e)
{
	int	out[2];
	int	res;

	out[0] = compute_outcode(img, s);
	out[1] = compute_outcode(img, e);
	res = jack_bauer(img, out, s, e);
	return (res);
}
