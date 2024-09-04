/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:23:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 14:00:15 by nzharkev         ###   ########.fr       */
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
		if (map->map_info)
		{
			ft_free_array(map->map_info);
			map->map_info = NULL;
		}
		if (map->dots_array)
		{
			free(map->dots_array);
			map->dots_array = NULL;
		}
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

	if (argc != 2)
		error(NULL, "Wrong argc");
	format_validation(argv[1]);
	set_up_fdf(&fdf);
	if (!fdf.mlx)
		error(NULL, "MLX fail");
	map_data(&fdf.map, argv[1]);
	three_dim(&fdf);
	two_dim(&fdf);
	background(&fdf, fdf.map.colour.background);
	draw_map(&fdf, fdf.map.dots_array);
	mlx_loop_hook(fdf.mlx, the_hook, &fdf);
	mlx_loop(fdf.mlx);
	if (fdf.image)
		mlx_delete_image(fdf.mlx, fdf.image);
	free(fdf.map.dots_array);
	mlx_terminate(fdf.mlx);
	return(0);
}
