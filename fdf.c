/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:23:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 10:58:25 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	the_hook(t_fdf *fdf)
{
	mlx_scroll_hook(fdf->mlx, the_scroll_hook, fdf);
	mlx_key_hook(fdf->mlx, &keypress, fdf);
}

void	insert_menu(t_fdf *fdf, char *str)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(str);
	if (!texture)
		error(fdf, &fdf->map, NULL);
	img = mlx_texture_to_image(fdf->mlx, texture);
	if (!texture)
	{
		mlx_delete_texture(texture);
		error(fdf, &fdf->map, NULL);
	}
	mlx_delete_texture(texture);
	mlx_image_to_window(fdf->mlx, img, 10, 10);
}

static void	make_window(t_fdf *fdf)
{
	int32_t	depth;

	make_image(fdf);
	depth = mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	mlx_set_instance_depth(fdf->image->instances, depth);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	insert_menu(fdf, "Menu.png");
	the_hook(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
}

void	make_image(t_fdf *fdf)
{
	fit_it(&fdf->map);
	center(&fdf->map, fdf->map.len);
	background(fdf, fdf->map.col.background);
	draw_map(fdf, fdf->map.dots);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		i;

	i = 0;
	if (argc != 2)
		error(NULL, NULL, "Wrong number of inputs");
	format_validation(argv[1]);
	map_data(&fdf, argv[1]);
	fdf.map.org_val = ft_calloc(fdf.map.len, sizeof(t_dot));
	if (!fdf.map.org_val)
		error(NULL, &fdf.map, "Malloc fail");
	copy_dots(fdf.map.dots, fdf.map.org_val, fdf.map.len);
	rotate_and_project(&fdf);
	colour_dots(&fdf.map, i);
	set_up_fdf(&fdf);
	make_window(&fdf);
	free(fdf.map.org_val);
	free(fdf.map.dots);
	return (0);
}
