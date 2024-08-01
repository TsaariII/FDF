/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:54:44 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/01 13:38:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*image;
}	t_fdf;

typedef struct	s_map
{
	t_pixel	*pixel_info;
	t_pixel	dimension;
	t_colours	colours;
	char	*map_info;
	int		len;
}	t_map;

typedef enum s_rgb
{
	RED,
	GREEN,
	BLUE,
	ALPHA
}	t_rgb;

typedef	struct s_colours
{
	int32_t top;
	int32_t bottom;
	int32_t background;
	int32_t base;
}	t_colours;

typedef	enum s_coordinates
{
	X,
	Y,
	Z,
}	t_coordinates;

typedef	struct s_pixel
{
	int32_t	colour;
	int32_t	colour_hex;
	float	axels[3];
}	t_pixel;

/*fdf.c*/


#endif
