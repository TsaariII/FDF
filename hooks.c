/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/27 10:26:10 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keypress(mlx_key_data_t data, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;

	//rotation(data, fdf);
	move_map(data, fdf);
	if (data.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(fdf->mlx);
		return ;
	}
	make_image(fdf);
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
	fit_it(&fdf->map);
	center(&fdf->map, fdf->map.len);
	background(fdf, fdf->map.colour.background);
	draw_map(fdf, fdf->map.dots_array);
}

void move_map(mlx_key_data_t data, t_fdf *fdf)
{
	if (data.key == MLX_KEY_D)
		fdf->map.x_move += 5;
	else if (data.key == MLX_KEY_A)
		fdf->map.x_move -= 5;
	else if (data.key == MLX_KEY_W)
		fdf->map.y_move -= 5;
	else if (data.key == MLX_KEY_S)
		fdf->map.y_move += 5;
}





// void	rotation(mlx_key_data_t key, t_fdf *fdf)
// {

// }


// void	the_hook(t_fdf *fdf)
// {
// 	t_fdf	*fdf;
// 	mlx_t	*mlx;

// 	fdf = param;
// 	mlx = fdf->mlx;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(fdf->mlx);

// }
