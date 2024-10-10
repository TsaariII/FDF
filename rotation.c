/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center(t_map *map, int len)
{
	t_dot	min;
	t_dot	max;
	t_dot	shift;
	int		i;

	get_min(map, &min);
	get_max(map, &max);
	shift.axis[X] = (WIDTH / 2)
		- ((max.axis[X] + min.axis[X]) / 2) + map->x_move;
	shift.axis[Y] = (HEIGHT / 2)
		- ((max.axis[Y] + min.axis[Y]) / 2) + map->y_move;
	shift.axis[Z] = 0;
	i = 0;
	while (i < len)
	{
		map->dots[i].axis[X] += shift.axis[X];
		map->dots[i].axis[Y] += shift.axis[Y];
		i++;
	}
}

void	positive(t_map *map)
{
	t_dot	min;
	t_dot	max;
	float	shift_x;
	float	shift_y;
	int		i;

	get_min(map, &min);
	get_max(map, &max);
	shift_x = -min.axis[X];
	shift_y = -min.axis[Y];
	i = 0;
	while (i < map->len)
	{
		map->dots[i].axis[X] += shift_x;
		map->dots[i].axis[Y] += shift_y;
		i++;
	}
}

void	to_isometric(t_dot *dot)
{
	double	temp_x;

	temp_x = dot->axis[X];
	dot->axis[X] = (temp_x - dot->axis[Y]) * \
		cos(0.523599);
	dot->axis[Y] = (temp_x + dot->axis[Y]) * \
		sin(0.523599) - dot->axis[Z];
}

void	rotate_and_project(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map.len)
	{
		fdf->map.dots[i] = fdf->map.org_val[i];
		fdf->map.dots[i].axis[Z] *= fdf->map.factor;
		fdf->map.dots[i].axis[Z] = fdf->map.dots[i].axis[Z] / 2;
		i++;
	}
	fdf->map.dim.axis[Z] /= 2;
	z_values(&fdf->map, fdf->map.dots, fdf->map.len);
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
