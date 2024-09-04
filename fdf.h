/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:54:44 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 10:08:31 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "MLX42/include/MLX42/MLX42.h"
//# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MARGIN 25
# define BIANCHI 0x1FF7D1
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFA00

# define Z_SCALE 20
# define X_ANGLE 30
# define Y_ANGLE 330
# define Z_ANGLE 30

# define M_PI 3.14159265358979323846

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
	char		**map_info;
	int			len;
	int			min_z;
	float		scale;
	t_pixel		*dots_array;
	t_pixel		dimension;
	t_pixel		origo;
	t_colours	colour;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*image;
}	t_fdf;

/*draw.c*/
void	draw_map(t_fdf *fdf, t_pixel *dots);

/*draw_utils.c*/
void	two_dim(t_fdf *fdf, float angle_x, float angle_y, float angle_z);
void	three_dim(t_fdf *fdf);

/*colours.c*/
int32_t	gradient(int colour_s, int colour_e, int len, int dot);
void	dot_colours(t_map *map, t_pixel *dots, t_colours colours);
void	background(t_fdf *fdf, __int32_t background);
int32_t paint_hexcolour(char *str);

/*fdf.c*/
int		little_big_endian(void);
void	format_validation(char *str);
int		error(t_map *map, char *error_msg);

/*initialize.c*/
void	base_colours(t_map *map);
void	base_pixel(uint8_t *buffer, int colour, int alpha);
void	dimensions(t_map *map);
void	kick_off_map(t_map *map);
void	set_up_fdf(t_fdf *fdf);

/*map_parse.c*/
void	map_data(t_map *map, char *file);

/*rotation.c*/
void    rotate_x(float *y, float *z, float angle);
void    rotate_y(float *x, float *z, float angle);
void    rotate_z(float *x, float *y, float angle);
void    projection(float *x, float *y, float *z);

/*utils.c*/
void	error_mlx(t_fdf *fdf);
//void	fit_it(t_fdf *fdf, t_pixel *dots);
void	uneven(int x, int line_num, t_map *map);
void	calculate_z(t_map *map, int id);
void	this_dot_is_valid(char *str, t_map *map);
//bool	valid_dot(t_pixel *dot);

#endif
