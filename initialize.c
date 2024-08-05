/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:07:52 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/05 15:58:01 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_up_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!fdf->mlx)
		error();
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
		error_mlx();
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) < 0)
		error_mlx();
}

void	base_colours(t_map *map)
{
	map->colours.background = BIANCHI;
	map->colours.top = WHITE;
	map->colours.bottom = BLACK;
	map->colours.base = YELLOW;
}

void	base_pixel(uint8_t *buffer, int colour, int alpha)
{
	if (little_big_endian() == 0)
	{
		buffer[R] = colour;
		buffer[G] = colour >> 8;
		buffer[B] = colour >> 16;
		buffer[A] =	alpha;
	}
	else
	{
		buffer[R] = colour >> 16;
		buffer[G] = colour >> 8;
		buffer[B] = colour;
		buffer[A] =	alpha;
	}
}

void	kick_off_map(t_map *map)
{
	map->map_info = NULL;
	map->dots_array = NULL;
	map->dimension.axels[X] = 0;
	map->dimension.axels[Y] = 0;
	map->dimension.axels[Z] = 0;
	map->len = 0;
	base_colours(map);
}

void	dimensions(t_map *map)
{
	int	w;
	int	h;
	int len;

	w = 0;
	h = 0;
	len = ft_strlen(map->map_info[0]);
	while (map->map_info[h])
	{
		w = 0;
		while (ft_isalnum(map->map_info[h][w]))
			w++;
		if (w != len)
			error();
		h++;
	}
	map->dimension[X] = w;
	map->dimension[Y] = h;
}
