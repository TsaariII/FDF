/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:23:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/25 14:49:25 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	format_validation(char *str)
{
	int len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		error(NULL, "Invalid file format");
}

static void make_image(t_fdf *fdf)
{
	fit_it(&fdf->map);
	//ft_zoom(&fdf->map, fdf->map.scale_xy, fdf->map.scale_z);
	center(&fdf->map, fdf->map.len);
	background(fdf, fdf->map.colour.background);
	draw_map(fdf, fdf->map.dots_array);
}

static void make_window(t_fdf *fdf)
{
	int32_t depth;

	make_image(fdf);
	depth = mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	mlx_set_instance_depth(fdf->image->instances, depth -1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_loop_hook(fdf->mlx, the_hook, fdf);
	mlx_scroll_hook(fdf->mlx, the_scroll_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		error(NULL, "Wrong number of inputs");
	format_validation(argv[1]);
	set_up_fdf(&fdf);
	if (!fdf.mlx)
		error(NULL, "MLX fail");
	map_data(&fdf, argv[1]);
	make_window(&fdf);
	// background(&fdf, fdf.map.colour.background);
	// draw_map(&fdf, fdf.map.dots_array);
	// mlx_loop_hook(fdf.mlx, the_hook, &fdf);
	// mlx_loop(fdf.mlx);
	// if (fdf.image)
	// 	mlx_delete_image(fdf.mlx, fdf.image);
	free(fdf.map.dots_array);
	//mlx_terminate(fdf.mlx);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_fdf	fdf;

// 	if (argc != 2)
// 		error(NULL, "Wrong number of inputs");
// 	format_validation(argv[1]);
// 	set_up_fdf(&fdf);
// 	if (!fdf.mlx)
// 		error(NULL, "MLX fail");
// 	map_data(&fdf, argv[1]);
// 	background(&fdf, fdf.map.colour.background);
// 	draw_map(&fdf, fdf.map.dots_array);
// 	mlx_loop_hook(fdf.mlx, the_hook, &fdf);
// 	mlx_loop(fdf.mlx);
// 	if (fdf.image)
// 		mlx_delete_image(fdf.mlx, fdf.image);
// 	free(fdf.map.dots_array);
// 	mlx_terminate(fdf.mlx);
// 	return (0);
// }
