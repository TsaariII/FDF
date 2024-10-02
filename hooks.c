/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/02 12:15:53 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keypress(mlx_key_data_t data, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;

	move_map(data, fdf);
	elevation(data, fdf);
	if (data.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(fdf->mlx);
		return ;
	}
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
	make_image(fdf);
}

void rotation(mlx_key_data_t data, t_fdf *fdf)
{
	if (data.key == MLX_KEY_D)
		fdf->map.z_rotate -= 0.02;
	else if (data.key  == MLX_KEY_A)
		fdf->map.z_rotate += 0.02;
	else if (data.key == MLX_KEY_W)
		fdf->map.x_rotate += 0.02;
	else if (data.key == MLX_KEY_S)
		fdf->map.x_rotate -= 0.02;
	rotate_and_project(fdf);
	colour_dots(&fdf->map, fdf->map.original_values, fdf->map.colour);
	make_image(fdf);
}

void move_map(mlx_key_data_t data, t_fdf *fdf)
{
	if (data.key == MLX_KEY_RIGHT)
		fdf->map.x_move += 5;
	else if (data.key == MLX_KEY_LEFT)
		fdf->map.x_move -= 5;
	else if (data.key == MLX_KEY_UP)
		fdf->map.y_move -= 5;
	else if (data.key == MLX_KEY_DOWN)
		fdf->map.y_move += 5;
	make_image(fdf);
}

void elevation(mlx_key_data_t data, t_fdf *fdf)
{
	if (data.key == MLX_KEY_P)
		fdf->map.factor *= 1.1;
	else if (data.key == MLX_KEY_M)
		fdf->map.factor *= 0.9;
	rotate_and_project(fdf);
	colour_dots(&fdf->map, fdf->map.dots_array, fdf->map.colour);
	make_image(fdf);
}

