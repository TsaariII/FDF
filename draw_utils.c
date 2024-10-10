/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min(t_map *map, t_dot *min)
{
	int	i;

	i = 0;
	min->axis[X] = map->dots[0].axis[X];
	min->axis[Y] = map->dots[0].axis[Y];
	while (i < map->len)
	{
		if (map->dots[i].axis[X] < min->axis[X])
			min->axis[X] = map->dots[i].axis[X];
		if (map->dots[i].axis[Y] < min->axis[Y])
			min->axis[Y] = map->dots[i].axis[Y];
		i++;
	}
}

void	get_max(t_map *map, t_dot *max)
{
	int	i;

	i = 0;
	max->axis[X] = map->dots[0].axis[X];
	max->axis[Y] = map->dots[0].axis[Y];
	while (i < map->len)
	{
		if (map->dots[i].axis[X] > max->axis[X])
			max->axis[X] = map->dots[i].axis[X];
		if (map->dots[i].axis[Y] > max->axis[Y])
			max->axis[Y] = map->dots[i].axis[Y];
		i++;
	}
}

void	ft_zoom(t_map *map, double zoom_xy, double zoom_z)
{
	int	i;

	i = 0;
	while (i < map->len)
	{
		if (zoom_xy)
		{
			map->dots[i].axis[X] *= zoom_xy;
			map->dots[i].axis[Y] *= zoom_xy;
		}
		if (zoom_z)
			map->dots[i].axis[Z] *= zoom_z;
		i++;
	}
}

void	fit_it(t_map *map)
{
	t_dot	min;
	t_dot	max;
	double	zoom_y;
	double	zoom_x;

	get_min(map, &min);
	get_max(map, &max);
	zoom_x = fabs(max.axis[X] - min.axis[X]) / (WIDTH - (MARGIN * 2));
	zoom_y = fabs(max.axis[Y] - min.axis[Y]) / (HEIGHT - (MARGIN * 2));
	zoom_x *= map->scale_xy;
	zoom_y *= map->scale_xy;
	if (zoom_y <= 0 || zoom_x <= 0)
		return ;
	ft_zoom(map, fmin(1 / zoom_y, 1 / zoom_x), map->scale_z);
}

void	z_values(t_map *map, t_dot *dots, int len)
{
	int	i;

	i = 0;
	map->min_z = map->dim.axis[Z];
	while (i < len)
	{
		if (dots[i].axis[Z] < map->min_z)
			map->min_z = map->dots[i].axis[Z];
		i++;
	}
	i = 0;
	while (i < map->len)
	{
		if (dots[i].axis[Z] > map->dim.axis[Z])
			map->dim.axis[Z] = dots[i].axis[Z];
		i++;
	}
}
