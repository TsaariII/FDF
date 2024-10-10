/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:31:08 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/10 11:07:16 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	coordinates(char *line, t_map *map, int line_num)
{
	int		h;
	int		id;
	char	**dots;

	h = 0;
	id = line_num * map->dim.axis[X];
	dots = ft_split(line, ' ');
	if (!dots)
		error(NULL, map, "Malloc fail");
	while (dots[h])
	{
		this_dot_is_valid(dots[h], map);
		if (ft_strchr(dots[h], ','))
			map->dots[id].col_hex = paint_hexcolour(dots[h]);
		map->dots[id].axis[X] = h - (map->dim.axis[X] - 1) / 2.0;
		map->dots[id].axis[Y] = line_num - (map->dim.axis[Y] / 2.0);
		map->dots[id].axis[Z] = ft_atoi(dots[h]);
		h++;
		id++;
	}
	ft_free_array(dots);
	if (h != map->dim.axis[X] && line_num != map->dim.axis[Y])
		uneven(++id, line_num, map);
	return (EXIT_SUCCESS);
}

void	create_coordinates(t_map *map)
{
	int		i;
	char	**temp;

	i = 0;
	temp = map->map_info;
	if (map->map_info[i] == NULL)
		error(NULL, NULL, "Invalid map");
	i = 0;
	while (temp[i])
	{
		coordinates(temp[i], map, i);
		i++;
	}
	z_values(map, map->dots, map->len);
}

static void	while_in_read(t_map *map, char *line, int fd)
{
	int		i;
	char	**temp;

	i = 1;
	while (line)
	{
		temp = map->map_info;
		line = get_next_line(fd);
		temp = ft_realloc(map->map_info, i
				* sizeof(char *), (i + 1) * sizeof(char *));
		if (!temp)
		{
			free(line);
			line = NULL;
			error(NULL, map, "Malloc fail");
		}
		map->map_info = temp;
		map->map_info[i] = line;
		if (line)
			i++;
	}
	free(line);
}

void	read_data(t_map *map, int fd)
{
	char	*line;
	int		i;

	map->map_info = malloc(1 * sizeof(char *));
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		error(NULL, NULL, "Empty file");
	}
	map->map_info[0] = line;
	i = 1;
	while_in_read(map, line, fd);
}

void	map_data(t_fdf *fdf, char *file)
{
	int	fd;

	kick_off_map(&fdf->map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, &fdf->map, "Open error");
	read_data(&fdf->map, fd);
	dimensions(&fdf->map);
	fdf->map.len = fdf->map.dim.axis[X] * fdf->map.dim.axis[Y];
	fdf->map.dots = ft_calloc(fdf->map.len, sizeof(t_dot));
	if (!fdf->map.dots)
	{
		ft_free_array(fdf->map.map_info);
		error(NULL, NULL, "Malloc fail");
	}
	create_coordinates(&fdf->map);
	ft_free_array(fdf->map.map_info);
	fdf->map.map_info = NULL;
	close(fd);
}
