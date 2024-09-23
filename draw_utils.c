/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/20 13:07:01 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min(t_map *map, t_dot *min)
{
	int i;

	i = 0;
	min->axels[X] = map->dots_array[0].axels[X];
	min->axels[Y] = map->dots_array[0].axels[Y];
	while (i < map->len)
	{
		if (map->dots_array[i].axels[X] < min->axels[X])
			min->axels[X] = map->dots_array[i].axels[X];
		if (map->dots_array[i].axels[Y] < min->axels[Y])
			min->axels[Y] = map->dots_array[i].axels[Y];
		i++;
	}
}

void	get_max(t_map *map, t_dot *max)
{
	int i;

	i = 0;
	max->axels[X] = map->dots_array[0].axels[X];
	max->axels[Y] = map->dots_array[0].axels[Y];
	while (i < map->len)
	{
		if (map->dots_array[i].axels[X] > max->axels[X])
			max->axels[X] = map->dots_array[i].axels[X];
		if (map->dots_array[i].axels[Y] > max->axels[Y])
			max->axels[Y] = map->dots_array[i].axels[Y];
		i++;
	}
}

static void	ft_zoom(t_map *map, double zoom)
{
	int i;

	i = 0;
	while (i < map->len)
	{
		map->dots_array[i].axels[X] *= zoom;
		map->dots_array[i].axels[Y] *= zoom;
		//map->dots_array[i].axels[Z] *= zoom;
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
	if (zoom_y <= 0 || zoom_x <= 0)
		return ;
	ft_zoom(map, fmin(1 / zoom_y, 1 / zoom_x));
}
