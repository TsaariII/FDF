/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 13:46:32 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	three_dim(t_fdf *fdf)
{
	int y;
	int x;
	int i;

	y = 0;
	i = 0;
	while (y < fdf->map.dimension.axels[Y])
	{
		x = 0;
		printf("map info %d: %s\n", y, fdf->map.map_info[y]);
		while (x < fdf->map.dimension.axels[X])
		{
			fdf->map.dots_array[i] = (t_pixel)
			{
				.axels = {y, x, fdf->map.map_info[y][x] - 48},
				.colour = 0
			};
			x++;
			i++;
		}
		y++;
	}
}

void	two_dim(t_fdf *fdf)
{
	int i;
	float x;
	float y;
	float z;

	i = 0;
	while (i < fdf->map.len)
	{
		x = fdf->map.dots_array[i].axels[X];
		y = fdf->map.dots_array[i].axels[Y];
		z = fdf->map.dots_array[i].axels[Z];
		rotate_x(&y, &z);
		rotate_y(&x, &z);
		rotate_z(&x, &y);
		projection(&x, &y, z);
		fdf->map.dots_array[i].axels[X] = x * fdf->map.scale;
		fdf->map.dots_array[i].axels[Y] = y * fdf->map.scale;
		i++;
	}
}
