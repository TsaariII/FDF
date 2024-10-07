/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:07:52 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/07 11:33:29 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	base_colours(t_map *map)
{
	map->col.background = BIANCHI;
	map->col.top = BLACK;
	map->col.bottom = YELLOW;
	map->col.base = WHITE;
}

void	set_up_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
		error(NULL, "MLX fail");
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
		error_mlx(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) < 0)
		error_mlx(fdf);
}

void	kick_off_map(t_map *map)
{
	map->map_info = NULL;
	map->dots = NULL;
	map->dim.axels[X] = 0;
	map->dim.axels[Y] = 0;
	map->dim.axels[Z] = 0;
	map->len = 0;
	map->scale_xy = 1;
	map->scale_z = 1;
	map->min_z = 0;
	map->factor = 1;
	map->origo.axels[X] = WIDTH / 2;
	map->origo.axels[Y] = HEIGHT / 2;
	map->origo.axels[Z] = 0;
	map->x_move = 0;
	map->y_move = 0;
	map->x_rot = 0;
	map->y_rot = 0;
	map->z_rot = 0;
	base_colours(map);
}

void	dimensions(t_map *map)
{
	int		h;
	int		w;
	int		len;
	char	**first;
	char	**current;

	h = 0;
	w = 0;
	first = ft_split(map->map_info[0], ' ');
	if (!first)
		error(map, "Malloc fail");
	len = ft_array_len(first);
	ft_free_array(first);
	while (map->map_info[h])
	{
		current = ft_split(map->map_info[h], ' ');
		w = ft_array_len(current);
		ft_free_array(current);
		if (w != len)
			error(map, "Inconsistent row length");
		h++;
	}
	map->dim.axels[X] = len;
	map->dim.axels[Y] = h;
}

void	base_pixel(uint8_t *buffer, int colour, int alpha)
{
	if (little_big_endian() == 0)
	{
		buffer[RED] = colour;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour >> 16;
		buffer[ALPHA] = alpha;
	}
	else
	{
		buffer[RED] = colour >> 16;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour;
		buffer[ALPHA] = alpha;
	}
}
