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
	parse_cub_file_map(path, map, type);
	print2d_array(map->map2d);
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
	{
		fprintf(stderr, "Error: Failed to open the file\n");
		exit(EXIT_FAILURE);
	}
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
	free(line);
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
		if (line[i] == '\n' || line[i] == '\0')
			return ;
		i++;
	}
    if (line[i] != '1' || line[ft_strlen(line)])
	{
		printf("Map error: map is not surrounded by 1");
		exit(1);
	}
    i = 0;
	line = trim_line(line, type);	
	while (line[i] != '\0')
	{
		if ((line[i] != 32) && !(line[i] >= 9 && line[i] <= 13)
			&& (line[i] != 'N') && (line[i] != 'S') && (line[i] != 'E')
			&& (line[i] != 'W') && (line[i] != '1') && (line[i] != '0')
			&& (line[i] != '2'))
		{
			printf("Error: the map contains wrong character: %c\n", line[i]);
			exit(1);
		}
		i++;
	}
	map->map2d[*index] = allocate_memory(ft_strlen(line), ARRAY, type);
	ft_strlcpy(map->map2d[*index], line, ft_strlen(line));
	printf("line len: %zu\n", ft_strlen(line));
    printf("line check %s\n", map->map2d[*index]);
	(*index)++;
}

char	*trim_line(char *line, t_type *type)
{
	char *new;
	int count_trim;
	size_t i = 0;
	count_trim = 0;
	int len = ft_strlen(line);

	new = allocate_memory(ft_strlen(line), ARRAY, type);

	while ((line[len - 1] == 32 || (line[len - 1] >= 9 && line[len - 1] <= 13)))
	{
		count_trim++;
		len--;
	}

	while (i <= ft_strlen(line) - count_trim)
	{

		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}