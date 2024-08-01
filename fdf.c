/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:23:19 by nzharkev          #+#    #+#             */
/*   Updated: 2024/07/31 11:00:39 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_pixel	*dots;

	if (argc != 2)
		error();
	format_validation(argv[1]);
	map_data(argv[1], &fdf.map);
	dots = ft_calloc(fdf.map.len, sizeof(t_pixel));
	if (!dots)
		error();
	draw_map(&fdf, dots);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.map.pixel_info);
	free(dots);
	mlx_terminate(fdf.mlx);
	return();
}
void	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		error();
}
