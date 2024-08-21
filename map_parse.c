/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:31:08 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/21 09:55:54 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**read_data(t_map *map, int fd)
{
	char	*line;
	char	*data;
	char	*temp;
	char 	**split_result;

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
			error(map,"Malloc fail");
		}
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	split_result = ft_split(data, '\n');
	return (split_result);
}


static int	dots_to_map(char *line, t_map *map, int line_num)
{
	int		h;
	int		id;
	char 	**dots;

	h = 0;
	id = 0;
	dots = ft_split(line, ' ');
	while (dots[h])
	{
		this_dot_is_valid(dots[h], map);
		map->dots_array[id].axels[X] = h - map->dimension.axels[X] / 2;
		map->dots_array[id].axels[Y] = line_num - map->dimension.axels[Y] / 2;
		map->dots_array[id].axels[Z] = ft_atoi(dots[h]);
		if (ft_strchr(dots[h], ','))
			map->dots_array[id].colour_hex = paint_hexcolour(dots[h]);
		calculate_z(map, id);
		h++;
		id++;
	}
	if (h != map->dimension.axels[X] && line_num != map->dimension.axels[Y])
		uneven(++id, line_num, map);
	return (EXIT_SUCCESS);
}

static void	dots_on_map(t_map *map)
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
		dots_to_map(temp[i], map, i);
		i++;
	}
	ft_free_array(temp);
}

void	map_data(t_map *map, char *file)
{
	int fd;

	kick_off_map(map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, "Open error");
	map->map_info = read_data(map, fd);
	dimensions(map);
	map->len = map->dimension.axels[X] * map->dimension.axels[Y];
	map->dots_array = ft_calloc(map->len, sizeof(t_pixel));
	if (!map->dots_array)
		error(NULL, "Malloc fail");
	dots_on_map(map);
	dot_colours(map, map->dots_array, map->colour);
	//free(map->map_info);
	map->map_info = NULL;
	close(fd);
}
