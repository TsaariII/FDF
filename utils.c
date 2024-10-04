/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:51:18 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/03 10:35:19 by nzharkev         ###   ########.fr       */
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
		if (map->dots)
		{
			free(map->dots);
			map->dots = NULL;
		}
	}
	ft_printf("%s\n", error_msg);
	exit (1);
}

void	uneven(int x, int line_num, t_map *map)
{
	map->dots[x].axels[Z] = 0;
	map->dots[x].axels[X] = map->dim.axels[X];
	map->dots[x].axels[Y] = line_num - map->dim.axels[Y] / 2;
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
			if (*str >= 'g' && *str <= 'z' && *str != 'x')
				error(map, "Invalid map");
		}
		else if (*str != 10)
			error(map, "Invalid map");
		str++;
	}
}

void	copy_dots(t_dot *src, t_dot *dest, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}
