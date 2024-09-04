/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:51:18 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 11:05:43 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_mlx(t_fdf *fdf)
{
	mlx_terminate(fdf->mlx);
	error(NULL, "MLX error");
}

void	this_dot_is_valid(char *str, t_map *map)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == ',' || *str == '-')
		{
			if (*str >= 'G' && *str <= 'Z' && *str != 'X')
				error(map, "Invalid map");
			if (*str >= 'g' && *str <= 'z' && *str !='x')
				error(map, "Invalid map");
		}
		else
			error(map, "Invalid map");
		str++;
	}
}

void	calculate_z(t_map *map, int id)
{
	if (map->dimension.axels[Z] < map->dots_array[id].axels[Z])
		map->dimension.axels[Z] = map->dots_array[id].axels[Z];
	if (map->dots_array[id].axels[Z] < map->min_z)
		map->min_z = map->dots_array[id].axels[Z];
}

void	uneven(int x, int line_num, t_map *map)
{
	map->dots_array[x].axels[Z] = 0;
	map->dots_array[x].axels[X] = map->dimension.axels[X];
	map->dots_array[x].axels[Y] = line_num - map->dimension.axels[Y] / 2;
}

int	ft_array_len(char **str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
/*static bool	inside_window(t_pixel *dots, int len)
{
	int a;

	a = 0;
	while (a < len)
	{
		if ((dots[a].axels[X] < MARGIN) || dots[a].axels[X] > WIDTH - MARGIN)
			return (false);
		if ((dots[a].axels[Y] < MARGIN) || dots[a].axels[Y] > HEIGHT - MARGIN)
			return (false);
		a++;
	}
	return (true);
}

void	fit_it(t_fdf *fdf, t_pixel *dots)
{
	copy_dots(fdf->map.dots_array, dots, fdf->map.len);
	geo_map_shaper(fdf, dots);
	while (!inside_window(dots, fdf->map.len))
	{
		fdf->map.scale -= 0.2;
		copy_dots(fdf->map.dots_array, dots, fdf->map.len);
		geo_map_shaper(fdf, dots);
	}
}


bool	valid_dot(t_pixel *dot)
{
	if (dot->axels[X] < 0 || dot->axels[X] > WIDTH)
		return (false);
	if (dot->axels[Y] < 0 || dot->axels[Y] > HEIGHT)
		return (false);
	else
		return (true);
}

void place_dot(mlx_image_t *image, float x, float y, int32_t colour)
{
	int dot;
	int alpha;
	alpha = 0xFF;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dot = ((int)round(y) * WIDTH * 4) + ((int)round(x) * 4);
	base_pixel(&image->pixels[dot], colour, alpha);
}*/
