/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:54:44 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:06:55 by nzharkev         ###   ########.fr       */
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
# include <stdint.h>
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
# define Y_ANGLE 30
# define Z_ANGLE 30

# define M_PI 3.14159265358979323846

# define INSIDE 0b0000
# define TOP 0b1000
# define BOTTOM 0b0100
# define RIGHT 0b0010
# define LEFT 0b0001

typedef enum s_rgb
{
	RED,
	GREEN,
	BLUE,
	ALPHA
}	t_rgb;

typedef struct s_colours
{
	int32_t	top;
	int32_t	bottom;
	int32_t	background;
	int32_t	base;
}	t_colours;

typedef enum s_coordinates
{
	X,
	Y,
	Z,
}	t_coordinates;

typedef struct s_dot
{
	int32_t	col;
	int32_t	col_hex;
	float	axis[3];
}	t_dot;

typedef struct s_map
{
	char		**map_info;
	int			len;
	int			min_z;
	float		factor;
	int			x_move;
	int			y_move;
	float		scale_xy;
	float		scale_z;
	float		x_rot;
	float		y_rot;
	float		z_rot;
	t_dot		*dots;
	t_dot		*org_val;
	t_dot		dim;
	t_dot		origo;
	t_colours	col;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*image;
}	t_fdf;

/*fdf.c*/
void	make_image(t_fdf *fdf);
void	insert_menu(t_fdf *fdf, char *str);

/*clip.c*/
int		clip_line(mlx_image_t *img, t_dot *s, t_dot *e);
int		compute_outcode(mlx_image_t *img, t_dot *dot);

/*clip2.c*/
void	clip_bottom(mlx_image_t *img, t_dot *s, t_dot *e, float xy[2]);
void	clip_top(t_dot *s, t_dot *e, float xy[2]);
void	clip_right(mlx_image_t *img, t_dot *s, t_dot *e, float xy[2]);
void	clip_left(t_dot *s, t_dot *e, float xy[2]);
void	update_xy(mlx_image_t *img, float *xy, int *out, t_dot *dot);

/*colours.c*/
int		little_big_endian(void);
int32_t	gradient(int colour_s, int colour_e, int len, int dot);
int32_t	paint_hexcolour(char *str);
void	background(t_fdf *fdf, __int32_t background);
void	colour_dots(t_map *map, int i);

/*draw.c*/
void	draw_map(t_fdf *fdf, t_dot *dots);

/*draw_utils.c*/
void	get_min(t_map *map, t_dot *min);
void	get_max(t_map *map, t_dot *max);
void	fit_it(t_map *map);
void	ft_zoom(t_map *map, double zoom_xy, double zoom_z);
void	z_values(t_map *map, t_dot *dots, int len);

/*hooks.c*/
void	keypress(mlx_key_data_t data, void *param);
void	the_scroll_hook(double xdelta, double ydelta, void *param);
void	zoom_image(t_fdf *fdf, double ydelta);
void	move_map(mlx_key_data_t data, t_fdf *fdf);
void	elevation(mlx_key_data_t data, t_fdf *fdf);

/*initilalize.c*/
void	base_pixel(uint8_t *buffer, int colour, int alpha);
void	dimensions(t_map *map);
void	kick_off_map(t_map *map);

/*map_parse.c*/
void	create_coordinates(t_map *map);
void	map_data(t_fdf *fdf, char *file);
void	read_data(t_map *map, int fd);

/*rotation.c*/
void	center(t_map *map, int len);
void	rotate_and_project(t_fdf *fdf);
void	positive(t_map *map);
void	to_isometric(t_dot *dot);

/*rotation2.c*/
void	rotate_x(t_map *map, t_dot *dot);
void	rotate_y(t_map *map, t_dot *dot);
void	rotate_z(t_map *map, t_dot *dot);
void	format_validation(char *str);
void	reset_map(t_fdf *fdf);

/*utils.c*/
void	base_colours(t_map *map);
void	set_up_fdf(t_fdf *fdf);
int		error(t_fdf *fdf, t_map *map, char *error_msg);
//void	error_mlx(t_fdf *fdf);
void	this_dot_is_valid(char *str, t_map *map);
void	uneven(int x, int line_num, t_map *map);
void	copy_dots(t_dot *src, t_dot *dest, int len);

#endif
