/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:54:44 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/05 16:35:23 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# define WIDTH 1920
# define HEIGHT 1080
# define BIANCHI 0x1FF7D1
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFA00

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

typedef struct	s_map
{
	t_pixel		*dots_array;
	t_pixel		dimension;
	t_colours	colour;
	char		**map_info;
	int			len;
	float		scale;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*image;
}	t_fdf;

/*draw.c*/
void	connect_dots(t_fdf *fdf, t_pixel *dots);
void	copy_dots(t_pixel *source, t_pixel *destination, int len);
void	draw_line(t_fdf *fdf, t_pixel start, t_pixel end);
void	draw_map(t_fdf *fdf, t_pixel *dots);
void	geo_map_shaper(t_fdf *fdf, t_pixel *dots);
void	place_pixel(mlx_image_t *image, float x, float y, int32_t colour);

/*draw_utils.c*/
t_pixel	multiply_matrix(float matrix[3][3], t_pixel dot);
void	scale_z(t_pixel *dots, t_map *map);
void	rotate_x(t_pixel *dots, t_pixel *projection, float angle, int len);
void	rotate_y(t_pixel *dots, t_pixel *projection, float angle, int len);
void	rotate_z(t_pixel *dots, t_pixel *projection, float angle, int len);
void	scale_dots(t_pixel *array, float scale, int len);
void	center(t_pixel *dots, t_pixel origo, int len);

/*colour.c*/
int32_t	gradient(int colour_s, int colour_e, int len, int dot);
void	dot_colours(t_map *map, t_pixel *dots, t_colours colours);
void	background(t_fdf *fdf, __int32_t background);

/*fdf.c*/
int		litte_big_endian(void);
void	format_validation(char *str);

/*initialize.c*/
void	base_colours(t_map *map);
void	base_pixel(uint8_t *buffer, int colour, int alpha);
void	dimensions(t_map *map);
void	kick_off_map(t_map *map);
void	set_up_fdf(t_fdf *fdf);

/*map_parse.c*/
void	map_data(t_map *map, char *file);

#endif
