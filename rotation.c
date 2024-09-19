/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/19 15:26:51 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void center(t_fdf *fdf, t_dot origo, int len)
// {
// 	int i;
// 	i = 0;
// 	while (i < len)
// 	{
// 		fdf->map.dots_array[i].axels[X] = fdf->map.dots_array[i].axels[X] + origo.axels[X];
// 		fdf->map.dots_array[i].axels[Y] = fdf->map.dots_array[i].axels[Y] + origo.axels[Y];
// 		fdf->map.dots_array[i].axels[Z] = fdf->map.dots_array[i].axels[Z] + origo.axels[Z];
// 		i++;
// 	}
// }

void rotate_and_project(t_fdf *fdf)
{
	int	i;
	double angle;
	double axis_angle;
	float x, y, z;

	i = 0;
	angle = 30 * (M_PI / 180);
	axis_angle = 120 * (M_PI / 180);
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
	fit_it(&fdf->map);
	//center(fdf, fdf->map.origo, fdf->map.len);
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
