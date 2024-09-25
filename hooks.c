/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/25 14:47:26 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	the_hook(void *param)
{
	t_fdf	*fdf;
	mlx_t	*mlx;

	fdf = param;
	mlx = fdf->mlx;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

void the_scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf *fdf;

	(void)xdelta;
	fdf = (t_fdf *)param;
	zoom_image(fdf, ydelta);
}

void zoom_image(t_fdf *fdf, double ydelta)
{
	if (ydelta > 0)
	{
		fdf->map.scale_xy *= 1.1;
		fdf->map.scale_z *= 1.1;
	}
	else
	{
		fdf->map.scale_xy *= 0.9;
		fdf->map.scale_z *= 0.9;
	}
	// rotate_and_project(fdf);
	// ft_zoom(&fdf->map, fdf->map.scale_xy, fdf->map.scale_xy);
	fit_it(&fdf->map);
	center(&fdf->map, fdf->map.len);
	background(fdf, fdf->map.colour.background);
	draw_map(fdf, fdf->map.dots_array);
}
