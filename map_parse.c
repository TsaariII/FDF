/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:31:08 by nzharkev          #+#    #+#             */
/*   Updated: 2024/08/01 14:58:23 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_data(t_map *map, char *file)
{
	int fd;

	kick_off_map(t_map *map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error();
	map->map_info = read_data(map, fd);
	lay_down_dimensions(map);
	map->len = map->dimension.axels[X] * map->dimension.axels[Y];
	map->pixel_info = ft_calloc(map->len, sizeof(t_pixel));
	if (!map->pixel_info)
		error();
	map_dots(map);
	dot_colours(mpa, map->pixel_info, map->colours);
	free(map->map_info);
	map->map_info = NULL;
	close(fd);
}

void	kick_off_map()
{
	map->map_info = NULL;
	map->pixel_info = NULL;
	map->dimension.axels[X] = 0;
	map->dimension.axels[Y] = 0;
	map->dimension.axels[Z] = 0;
	map->len = 0;
}

static char	*read_map(t_map *map, int fd)
{
	char	*line;
	char	*data;
	char	*temp;

	data = ft_calloc(1, sizeof(char));
	if (!data)
		error();
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = data;
		data = ft_strjoin(data, line);
		if (!data)
		{
			free(line);
			free(temp);
			error();
		}
		free(temp);
		free(line);
	}
	return (data);
}
