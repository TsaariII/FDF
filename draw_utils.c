/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/09 17:24:09 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min(t_map *map, t_dot *min)
{
	int	i;

	i = 0;
	min->axels[X] = map->dots[0].axels[X];
	min->axels[Y] = map->dots[0].axels[Y];
	while (i < map->len)
	{
		if (map->dots[i].axels[X] < min->axels[X])
			min->axels[X] = map->dots[i].axels[X];
		if (map->dots[i].axels[Y] < min->axels[Y])
			min->axels[Y] = map->dots[i].axels[Y];
		i++;
	}
}

void	get_max(t_map *map, t_dot *max)
{
	int	i;

	i = 0;
	max->axels[X] = map->dots[0].axels[X];
	max->axels[Y] = map->dots[0].axels[Y];
	while (i < map->len)
	{
		if (map->dots[i].axels[X] > max->axels[X])
			max->axels[X] = map->dots[i].axels[X];
		if (map->dots[i].axels[Y] > max->axels[Y])
			max->axels[Y] = map->dots[i].axels[Y];
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
			map->dots[i].axels[X] *= zoom_xy;
			map->dots[i].axels[Y] *= zoom_xy;
		}
		if (zoom_z)
			map->dots[i].axels[Z] *= zoom_z;
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
	zoom_x = fabs(max.axels[X] - min.axels[X]) / (WIDTH - (MARGIN * 2));
	zoom_y = fabs(max.axels[Y] - min.axels[Y]) / (HEIGHT - (MARGIN * 2));
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
	map->min_z = map->dim.axels[Z];
	while (i < len)
	{
		if (dots[i].axels[Z] < map->min_z)
			map->min_z = map->dots[i].axels[Z];
		i++;
	}
	i = 0;
	while (i < map->len)
	{
		if (dots[i].axels[Z] > map->dim.axels[Z])
			map->dim.axels[Z] = dots[i].axels[Z];
		i++;
	}
}
