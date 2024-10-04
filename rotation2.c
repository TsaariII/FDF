/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:39:24 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/04 12:32:54 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_map *map, t_dot *dot)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = dot->axels[X];
	tmp_y = dot->axels[Y];
	dot->axels[X] = tmp_x * cos(map->z_rot) - tmp_y * sin(map->z_rot);
	dot->axels[Y] = tmp_x * sin(map->z_rot) + tmp_y * cos(map->z_rot);
}

void	rotate_y(t_map *map, t_dot *dot)
{
	double	tmp_x;

	tmp_x = dot->axels[X];
	dot->axels[X] = tmp_x * cos(map->y_rot) + \
		dot->axels[Z] * sin(map->y_rot);
	dot->axels[Z] = dot->axels[Z] * \
		cos(map->y_rot) - tmp_x * sin(map->y_rot);
}

void	rotate_x(t_map *map, t_dot *dot)
{
	double	tmp_y;

	tmp_y = dot->axels[Y];
	dot->axels[Y] = tmp_y * cos(map->x_rot) - \
		dot->axels[Z] * sin(map->x_rot);
	dot->axels[Z] = tmp_y * sin(map->x_rot) + \
		dot->axels[Z] * cos(map->x_rot);
}

void	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		error(NULL, "Invalid file format");
}

void	reset_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map.len)
	{
		fdf->map.dots[i] = fdf->map.org_val[i];
		fdf->map.dots[i].axels[Z] *= fdf->map.factor;
		fdf->map.dots[i].axels[Z] = fdf->map.dots[i].axels[Z] / 2;
		i++;
	}
	fdf->map.dim.axels[Z] = 1;
	z_values(&fdf->map, fdf->map.org_val, fdf->map.len);
	fdf->map.dim.axels[Z] /= 2;
	i = 0;
	while (i < fdf->map.len)
	{
		rotate_z(&fdf->map, &fdf->map.dots[i]);
		rotate_x(&fdf->map, &fdf->map.dots[i]);
		rotate_y(&fdf->map, &fdf->map.dots[i]);
		to_isometric(&fdf->map.dots[i]);
		i++;
	}
	positive(&fdf->map);
}
