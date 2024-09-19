/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:07:52 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/19 15:26:13 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	map->dots_array = NULL;
	map->dimension.axels[X] = 0;
	map->dimension.axels[Y] = 0;
	map->dimension.axels[Z] = 0;
	map->len = 0;
	map->scale = 50;
	map->min_z = 0;
	map->origo.axels[X] = WIDTH / 2;
	map->origo.axels[Y] = HEIGHT / 2;
	map->origo.axels[Z] = 0;
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
	map->dimension.axels[X] = len;
	map->dimension.axels[Y] = h;
}

void	base_colours(t_map *map)
{
	map->colour.background = BLACK;
	map->colour.top = WHITE;
	map->colour.bottom = YELLOW;
	map->colour.base = BIANCHI;
}

void	base_pixel(uint8_t *buffer, int colour, int alpha)
{
	if (little_big_endian() == 0)
	{
		buffer[RED] = colour;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour >> 16;
		buffer[ALPHA] =	alpha;
	}
	else
	{
		buffer[RED] = colour >> 16;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour;
		buffer[ALPHA] =	alpha;
	}
}

void z_values(t_map *map)
{
	int i;
	i = 0;
	while (i < map->len)
	{
		if (map->dots_array[i].axels[Z] < map->min_z)
			map->min_z = map->dots_array[i].axels[Z];
		i++;
	}
	i = 0;
	while (i < map->len)
	{
		if (map->dots_array[i].axels[Z] > map->dimension.axels[Z])
			map->dimension.axels[Z] = map->dots_array[i].axels[Z];
		i++;
	}
}
