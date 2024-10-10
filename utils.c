/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:51:18 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:01:07 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error(t_fdf *fdf, t_map *map, char *error_msg)
{
	if (fdf)
	{
		mlx_terminate(fdf->mlx);
		error(NULL, &fdf->map, "MLX error");
	}
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

void	set_up_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
		error(NULL, &fdf->map, NULL);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
		error(fdf, NULL, NULL);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) < 0)
		error(fdf, NULL, NULL);
}

void	this_dot_is_valid(char *str, t_map *map)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == ',' || *str == '-')
		{
			if (*str >= 'G' && *str <= 'Z' && *str != 'X')
				error(NULL, map, "Invalid map");
			if (*str >= 'g' && *str <= 'z' && *str != 'x')
				error(NULL, map, "Invalid map");
		}
		else if (*str != 10)
			error(NULL, map, "Invalid map");
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
