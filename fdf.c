/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:23:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 10:21:18 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
void	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		error(NULL, "Invalid file format");
}

int	little_big_endian(void)
{
	int	endian;
	int16_t	x;

	x = 0x0001;
	endian = (*((int8_t *)(&x)) == 0x01);
	return (endian);
}

int	error(t_map *map, char *error_msg)
{
	if (map)
	{
		free(map->map_info);
		free(map->dots_array);
	}
	ft_printf("%s\n", error_msg);
	exit (1);
}
static void	the_hook(void *param)
{
	t_fdf	*fdf;
	mlx_t	*mlx;

	fdf = param;
	mlx = fdf->mlx;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	float	angle_x;
	float	angle_y;
	float	angle_z;

	angle_x = X_ANGLE * M_PI / 180;
	angle_y = Y_ANGLE * M_PI / 180;
	angle_z = Z_ANGLE * M_PI / 180;
	if (argc != 2)
		error(NULL, "Wrong argc");
	format_validation(argv[1]);
	set_up_fdf(&fdf);
	map_data(&fdf.map, argv[1]);
	three_dim(&fdf);
	two_dim(&fdf, angle_x, angle_y, angle_z);
	background(&fdf, fdf.map.colour.background);
	draw_map(&fdf, fdf.map.dots_array);
	mlx_loop(fdf.mlx);
	mlx_loop_hook(fdf.mlx, the_hook, &fdf);
	free(fdf.map.dots_array);
	mlx_terminate(fdf.mlx);
	return(0);
}
