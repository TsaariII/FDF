/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:31:08 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/19 15:26:30 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**read_data(t_map *map, int fd)
{
	char	*line;
	char	*data;
	char	*temp;
	char	**split_res;

	data = ft_calloc(1, sizeof(char));
	if (!data)
		error(map, "Malloc fail");
	line = get_next_line(fd);
	while (line)
	{
		temp = data;
		data = ft_strjoin(data, line);
		if (!data)
		{
			free(line);
			free(temp);
			error(map, "Malloc fail");
		}
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	split_res = ft_split(data, '\n');
	free(data);
	return (split_res);
}

static int	coordinates(char *line, t_map *map, int line_num)
{
	int		h;
	int		id;
	char	**dots;

	h = 0;
	id = line_num * map->dimension.axels[X];
	dots = ft_split(line, ' ');
	if (!dots)
		error(map, "Malloc fail");
	while (dots[h])
	{
		this_dot_is_valid(dots[h], map);
		map->dots_array[id].axels[X] = h - (map->dimension.axels[X] - 1) / 2.0;
		map->dots_array[id].axels[Y] = line_num - (map->dimension.axels[Y] / 2.0);
		map->dots_array[id].axels[Z] = ft_atoi(dots[h]);
		h++;
		id++;
	}
	ft_free_array(dots);
	if (h != map->dimension.axels[X] && line_num != map->dimension.axels[Y])
		uneven(++id, line_num, map);
	return (EXIT_SUCCESS);
}

static void	create_coordinates(t_map *map)
{
	int		i;
	char	**temp;

	i = 0;
	temp = map->map_info;
	if (map->map_info[i] == NULL)
		error(NULL, "Invalid map");
	i = 0;
	while (temp[i])
	{
		coordinates(temp[i], map, i);
		i++;
	}
	z_values(map);
}

void	map_data(t_fdf *fdf, char *file)
{
	int fd;

	kick_off_map(&fdf->map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(&fdf->map, "Open error");
	fdf->map.map_info = read_data(&fdf->map, fd);
	dimensions(&fdf->map);
	fdf->map.len = fdf->map.dimension.axels[X] * fdf->map.dimension.axels[Y];
	fdf->map.dots_array = ft_calloc(fdf->map.len, sizeof(t_dot));
	if (!fdf->map.dots_array)
	{
		ft_free_array(fdf->map.map_info);
		error(NULL, "Malloc fail");
	}
	create_coordinates(&fdf->map);
	rotate_and_project(fdf);
	colour_dots(&fdf->map, fdf->map.dots_array, fdf->map.colour);
	ft_free_array(fdf->map.map_info);
	fdf->map.map_info = NULL;
	close(fd);
}
