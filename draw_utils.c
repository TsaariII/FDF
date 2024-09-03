/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:19:28 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/03 14:16:50 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	three_dim(t_fdf *fdf)
{
	int y;
	int x;

	fdf->map.dots_array = malloc(fdf->map.dimension.axels[Y] * fdf->map.dimension.axels[X] * sizeof(t_pixel));
	if (!fdf->map.dots_array)
		error(&fdf->map, "Malloc failed");
	y = 0;
	while (y < fdf->map.dimension.axels[Y])
	{
		x = 0;
		while (x < fdf->map.dimension.axels[X])
		{
			fdf->map.dots_array.[y * fdf->map.dimensions.axels[X] + y] =
			(t_pixel){
				.axels = {y, x, fdf->map.map_info[y][x] - 48},
				.colour = 0
			};
			x++;
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
		rotate_x(&y, &z, (X_ANGLE * M_PI / 180));
		rotate_y(&x, &z, (Y_ANGLE * M_PI / 180));
		rotate_z(&x, &y, (Z_ANGLE * M_PI / 180));
		projection(&x, &y, &z);
		fdf->map.dots_array[i].axels[X] = x * fdf->map.scale;
		fdf->map.dots_array[i].axels[Y] = y * fdf->map.scale;
		i++;
	}
}
