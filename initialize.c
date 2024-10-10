/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:07:52 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:00:25 by nzharkev         ###   ########.fr       */
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

static int	while_in_dimensions(t_map *map, int h, int len)
{
	char	**current;
	int		w;

	while (map->map_info[h])
	{
		current = ft_split(map->map_info[h], ' ');
		if (!current)
			error(NULL, map, "Malloc fail");
		w = ft_array_len(current);
		ft_free_array(current);
		if (w != len)
			error(NULL, map, "Inconsistent row length");
		h++;
	}
	return (h);
}

void	dimensions(t_map *map)
{
	int		h;
	int		w;
	int		len;
	char	**first;

	h = 0;
	w = 0;
	first = ft_split(map->map_info[0], ' ');
	if (!first)
		error(NULL, map, "Malloc fail");
	len = ft_array_len(first);
	ft_free_array(first);
	h = while_in_dimensions(map, h, len);
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
