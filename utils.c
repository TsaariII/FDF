/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:51:18 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/30 10:09:49 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error(t_map *map, char *error_msg)
{
	if (map)
	{
		if (map->map_info)
		{
			ft_free_array(map->map_info);
			map->map_info = NULL;
		}
		if (map->dots_array)
		{
			free(map->dots_array);
			map->dots_array = NULL;
		}
	}
	ft_printf("%s\n", error_msg);
	exit (1);
}

void	uneven(int x, int line_num, t_map *map)
{
	map->dots_array[x].axels[Z] = 0;
	map->dots_array[x].axels[X] = map->dimension.axels[X];
	map->dots_array[x].axels[Y] = line_num - map->dimension.axels[Y] / 2;
}

void	error_mlx(t_fdf *fdf)
{
	mlx_terminate(fdf->mlx);
	error(&fdf->map, "MLX error");
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
		else if (*str != 10)
			error(map, "Invalid map");
		str++;
	}
}

void	copy_dots(t_dot *src, t_dot *dest, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}
