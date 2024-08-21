/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:00:02 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/21 13:04:34 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*set_map(char *path)
{
	static t_map	*map;
	t_type			*type;
	t_specs			*specs;

	specs = get_specs();
	type = NULL;
	map = allocate_memory(0, MAP, type);
	map->map2d = allocate_memory(specs->rows, ARRAY2D, type);
	map->check = allocate_memory(specs->rows, ARRAY2D, type);
	parse_cub_file_map(path, map, type);
	check_players(map->map2d, map);
	final_map_check_dfs(map->map2d, map);
	get_map_parameters(map, map->map2d);
	return (map);
}

t_map	*get_map(void)
{
	static t_map	*map;

	if (!map)
	{
		printf("Error: Failed to load the specs");
		exit(1);
	}
	return (map);
}

void	parse_cub_file_map(char *path, t_map *map, t_type *type)
{
	char	*line;
	int		fd;
	int		tracker;
	int		index;

	tracker = 0;
	index = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_and_exit_map("Error: failed to open a map.", map, NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (tracker == 6)
			build_map2d(line, map, type, &index);
		else
			check_tracker(line, &tracker);
		free(line);
		line = get_next_line(fd);
	}
}

void	check_tracker(char *line, int *tracker)
{
	int	i;

	i = 0;
	if (*tracker == 6)
		return ;
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		&& line[i] != '\0')
		i++;
	if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i
				+ 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'F' && line[i
				+ 1] == 32) || (line[i] == 'C' && line[i + 1] == 32))
	{
		(*tracker)++;
	}
}

void	build_map2d(char *line, t_map *map, t_type *type, int *index)
{
	int	i;

	i = 0;
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
	{
		if (*index == 0 && (line[i] == '\n' || line[i] == '\0'))
			return ;
		i++;
	}
	line = trim_line(line, type);
	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] != 32) && !(line[i] >= 9 && line[i] <= 13)
			&& (line[i] != 'N') && (line[i] != 'S') && (line[i] != 'E')
			&& (line[i] != 'W') && (line[i] != '1') && (line[i] != '0'))
			print_and_exit_map("Error: Your map is not valid.", map,
				&line);
	}
	map->map2d[*index] = ft_strdup(line);
	map->check[*index] = ft_strdup(line);
	free(line);
	line = NULL;
	(*index)++;
}
