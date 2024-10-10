/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:39:24 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_map *map, t_dot *dot)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = dot->axis[X];
	tmp_y = dot->axis[Y];
	dot->axis[X] = tmp_x * cos(map->z_rot) - tmp_y * sin(map->z_rot);
	dot->axis[Y] = tmp_x * sin(map->z_rot) + tmp_y * cos(map->z_rot);
}

void	rotate_y(t_map *map, t_dot *dot)
{
	double	tmp_x;

	tmp_x = dot->axis[X];
	dot->axis[X] = tmp_x * cos(map->y_rot) + \
		dot->axis[Z] * sin(map->y_rot);
	dot->axis[Z] = dot->axis[Z] * \
		cos(map->y_rot) - tmp_x * sin(map->y_rot);
}

void	rotate_x(t_map *map, t_dot *dot)
{
	double	tmp_y;

	tmp_y = dot->axis[Y];
	dot->axis[Y] = tmp_y * cos(map->x_rot) - \
		dot->axis[Z] * sin(map->x_rot);
	dot->axis[Z] = tmp_y * sin(map->x_rot) + \
		dot->axis[Z] * cos(map->x_rot);
}

void	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		error(NULL, NULL, "Invalid file format");
}

void	reset_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->map.x_move = 0;
	fdf->map.y_move = 0;
	while (i < fdf->map.len)
	{
		fdf->map.dots[i] = fdf->map.org_val[i];
		fdf->map.dots[i].axis[Z] *= fdf->map.factor;
		fdf->map.dots[i].axis[Z] = fdf->map.dots[i].axis[Z] / 2;
		i++;
	}
	fdf->map.dim.axis[Z] = 1;
	z_values(&fdf->map, fdf->map.org_val, fdf->map.len);
	fdf->map.dim.axis[Z] /= 2;
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
