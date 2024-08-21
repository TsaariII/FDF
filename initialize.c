/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:07:52 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/21 09:39:07 by nzharkev         ###   ########.fr       */
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

void	base_colours(t_map *map)
{
	map->colour.background = BIANCHI;
	map->colour.top = WHITE;
	map->colour.bottom = BLACK;
	map->colour.base = YELLOW;
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
	int	j;
	int len;

	w = 0;
	h = 0;
	len = ft_countchar(map->map_info[0], ' ');
	while (map->map_info[h])
	{
		w = 0;
		j = 0;
		while (j <= (int)ft_strlen(map->map_info[h]))
		{
			if (ft_isdigit(map->map_info[h][j]))
				w++;
			j++;
		}
		if (w != len)
			error(NULL, "Invalid map");
		h++;
	}
	map->dimension.axels[X] = w;
	map->dimension.axels[Y] = h;
}
