/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/02 11:24:55 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void center(t_map *map, int len)
{
	t_dot min;
	t_dot max;
	t_dot shift;
	int i;

	get_min(map, &min);
	get_max(map, &max);
	shift.axels[X] = (WIDTH / 2) - ((max.axels[X] + min.axels[X]) / 2) + map->x_move;
	shift.axels[Y] = (HEIGHT / 2) - ((max.axels[Y] + min.axels[Y]) / 2) + map->y_move;
	shift.axels[Z] = 0;
	i = 0;
	while (i < len)
	{
		map->dots_array[i].axels[X] += shift.axels[X];
		map->dots_array[i].axels[Y] += shift.axels[Y];
		i++;
	}
}

void positive(t_map *map)
{
 	t_dot min;
 	t_dot max;
	float shift_x;
	float shift_y;
	int i;

	get_min(map, &min);
	get_max(map, &max);
	shift_x = -min.axels[X];
	shift_y = -min.axels[Y];
	i = 0;
	while (i < map->len)
	{
		map->dots_array[i].axels[X] += shift_x;
		map->dots_array[i].axels[Y] += shift_y;
		i++;
	}
}
static void	to_isometric(
	t_dot *dot)
{
	double	temp_x;

	temp_x = dot->axels[X];
	dot->axels[X] = (temp_x - dot->axels[Y]) * \
		cos(0.523599);
	dot->axels[Y] = (temp_x + dot->axels[Y]) * \
		sin(0.523599) - dot->axels[Z];
}

static void	rotate_z(t_map *map, t_dot *dot)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = dot->axels[X];
	tmp_y = dot->axels[Y];
	dot->axels[X] = tmp_x * cos(map->z_rotate) - tmp_y * sin(map->z_rotate);
	dot->axels[Y] = tmp_x * sin(map->z_rotate) + tmp_y * cos(map->z_rotate);
}

static void	rotate_y(t_map *map, t_dot *dot)
{
	double	tmp_x;

	tmp_x = dot->axels[X];
	dot->axels[X] = tmp_x * cos(map->y_rotate) + \
		dot->axels[Z] * sin(map->y_rotate);
	dot->axels[Z] = dot->axels[Z] * \
		cos(map->y_rotate) - tmp_x * sin(map->y_rotate);
}

static void	rotate_x(t_map *map, t_dot *dot)
{
	double	tmp_y;

	tmp_y = dot->axels[Y];
	dot->axels[Y] = tmp_y * cos(map->x_rotate) - \
		dot->axels[Z] * sin(map->x_rotate);
	dot->axels[Z] = tmp_y * sin(map->x_rotate) + \
		dot->axels[Z] * cos(map->x_rotate);
}

void rotate_and_project(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map.len)
	{
		fdf->map.dots_array[i] = fdf->map.original_values[i];
		fdf->map.dots_array[i].axels[Z] *= fdf->map.factor;
		fdf->map.dots_array[i].axels[Z] = fdf->map.dots_array[i].axels[Z] / 2;
		i++;
	}
	fdf->map.dimension.axels[Z]/= 2;
	z_values(&fdf->map);
	i = 0;
	while (i < fdf->map.len)
	{
		rotate_z(&fdf->map, &fdf->map.dots_array[i]);
		rotate_x(&fdf->map, &fdf->map.dots_array[i]);
		rotate_y(&fdf->map, &fdf->map.dots_array[i]);
		to_isometric(&fdf->map.dots_array[i]);
		i++;
	}
	positive(&fdf->map);
}
