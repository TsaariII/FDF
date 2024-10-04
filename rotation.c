/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/04 12:27:43 by nzharkev         ###   ########.fr       */
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
	shift.axels[X] = (WIDTH / 2)
		- ((max.axels[X] + min.axels[X]) / 2) + map->x_move;
	shift.axels[Y] = (HEIGHT / 2)
		- ((max.axels[Y] + min.axels[Y]) / 2) + map->y_move;
	shift.axels[Z] = 0;
	i = 0;
	while (i < len)
	{
		map->dots[i].axels[X] += shift.axels[X];
		map->dots[i].axels[Y] += shift.axels[Y];
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
	shift_x = -min.axels[X];
	shift_y = -min.axels[Y];
	i = 0;
	while (i < map->len)
	{
		map->dots[i].axels[X] += shift_x;
		map->dots[i].axels[Y] += shift_y;
		i++;
	}
}

void	to_isometric(t_dot *dot)
{
	double	temp_x;

	temp_x = dot->axels[X];
	dot->axels[X] = (temp_x - dot->axels[Y]) * \
		cos(0.523599);
	dot->axels[Y] = (temp_x + dot->axels[Y]) * \
		sin(0.523599) - dot->axels[Z];
}

void	rotate_and_project(t_fdf *fdf)
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
	fdf->map.dim.axels[Z] /= 2;
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
