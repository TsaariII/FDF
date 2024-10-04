/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:02:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/03 10:34:04 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_xy(mlx_image_t *img, float *xy, int *out, t_dot *dot)
{
	dot->axels[X] = xy[0];
	dot->axels[Y] = xy[1];
	*out = compute_outcode(img, dot);
}

void	clip_bottom(mlx_image_t *img, t_dot *s, t_dot *e, float xy[2])
{
	xy[0] = s->axels[X] + (e->axels[X] - s->axels[X])
		* ((img->height - 1) - s->axels[Y]) / (e->axels[Y] - s->axels[Y]);
	xy[1] = img->height - 1;
}

void	clip_top(t_dot *s, t_dot *e, float xy[2])
{
	xy[0] = s->axels[X] + (e->axels[X] - s->axels[X])
		* (1 - s->axels[Y]) / (e->axels[Y] - s->axels[Y]);
	xy[1] = 1;
}

void	clip_right(mlx_image_t *img, t_dot *s, t_dot *e, float xy[2])
{
	xy[0] = img->width - 1;
	xy[1] = s->axels[Y] + (e->axels[Y] - s->axels[Y])
		* ((img->width - 1) - s->axels[X]) / (e->axels[X] - s->axels[X]);
}

void	clip_left(t_dot *s, t_dot *e, float xy[2])
{
	xy[0] = 1;
	xy[1] = s->axels[Y] + (e->axels[Y] - s->axels[Y])
		* (1 - s->axels[X]) / (e->axels[X] - s->axels[X]);
}
