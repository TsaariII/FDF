/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/25 14:17:12 by nzharkev         ###   ########.fr       */
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
	shift.axels[X] = (WIDTH / 2) - ((max.axels[X] + min.axels[X]) / 2);
	shift.axels[Y] = (HEIGHT / 2) - ((max.axels[Y] + min.axels[Y]) / 2);
	shift.axels[Z] = 0;
	i = 0;
	while (i < len)
	{
		map->dots_array[i].axels[X] += shift.axels[X];
		map->dots_array[i].axels[Y] += shift.axels[Y];
		i++;
	}
}

void rotate_and_project(t_fdf *fdf)
{
	int	i;
	double angle;
	double axis_angle;
	float x, y, z;

	i = 0;
	angle = 30 * (M_PI / 180);
	axis_angle = 110 * (M_PI / 180);
	while (i < fdf->map.len)
	{
		x = fdf->map.dots_array[i].axels[X];
		y = fdf->map.dots_array[i].axels[Y];
		z = fdf->map.dots_array[i].axels[Z];
		fdf->map.dots_array[i].axels[X] = (x * cos(angle)) + (y * cos(angle + axis_angle))
		 	+ (z * cos(angle - axis_angle));
		fdf->map.dots_array[i].axels[Y] = (x * sin(angle)) + (y * sin(angle + axis_angle))
		 	+ (z * sin(angle - axis_angle));
		i++;
	}
	positive(&fdf->map);
	//fit_it(&fdf->map);
	//center(&fdf->map, fdf->map.len);
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
