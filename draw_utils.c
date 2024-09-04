/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 10:28:35 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	three_dim(t_fdf *fdf)
{
	int y;
	int x;
	int i;

	fdf->map.dots_array = malloc(fdf->map.dimension.axels[Y] * fdf->map.dimension.axels[X] * sizeof(t_pixel));
	if (!fdf->map.dots_array)
		error(&fdf->map, "Malloc failed");
	y = 0;
	i = 0;
	while (y < fdf->map.dimension.axels[Y])
	{
		x = 0;
		while (x < fdf->map.dimension.axels[X])
		{
			fdf->map.dots_array[i] = (t_pixel)
			{
				.axels = {y, x, fdf->map.map_info[y][x] - 48},
				.colour = 0
			};
			x++;
		}
		y++;
	}
}

void	two_dim(t_fdf *fdf, float angle_x, float angle_y, float angle_z)
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
		rotate_x(&y, &z, angle_x);
		rotate_y(&x, &z, angle_y);
		rotate_z(&x, &y, angle_z);
		projection(&x, &y, z);
		fdf->map.dots_array[i].axels[X] = x * fdf->map.scale;
		fdf->map.dots_array[i].axels[Y] = y * fdf->map.scale;
		i++;
	}
}
