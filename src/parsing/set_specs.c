#include "cub3d.h"

t_specs	*set_specs(char *path)
{
	static t_specs	*specs;
	t_type			*type;

	if (specs)
		return (specs);
	type = NULL;
	specs = allocate_memory(0, SPECS, type);
	specs->rows = 0;
	parse_cub_file_specs(path, specs, type);
	return (specs);
}

t_specs	*get_specs(void)
{
	static t_specs	*specs;

	if (!specs)
		specs = set_specs(NULL);
	return (specs);
}

void	parse_cub_file_specs(char *path, t_specs *specs, t_type *type)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		check_line(line, specs, type);
		free(line);
		line = get_next_line(fd);
		specs->rows++;
	}
	free(line);
	printf("check specs rows %d\n", specs->rows);
}

void	check_line(char *line, t_specs *specs, t_type *type)
{
	int	i;

	i = 0;
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		&& line[i] != '\0')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		specs->n_spec = get_path(line, specs->n_spec, type, 2);
		printf("checking n->specs: %s\n", specs->n_spec);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		specs->s_spec = get_path(line, specs->s_spec, type, 2);
		printf("checking s->specs: %s\n", specs->s_spec);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		specs->w_spec = get_path(line, specs->w_spec, type, 2);
		printf("checking w->specs: %s\n", specs->w_spec);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		specs->e_spec = get_path(line, specs->e_spec, type, 2);
		printf("checking e->specs: %s\n", specs->e_spec);
	}
	else if (line[i] == 'F' && line[i + 1] == 32)
	{
		specs->floor_spec = get_path(line, specs->floor_spec, type, 0);
		printf("checking floor_spec: %s\n", specs->floor_spec);
	}
	else if (line[i] == 'C' && line[i + 1] == 32)
	{
		specs->ceil_spec = get_path(line, specs->ceil_spec, type, 0);
		printf("checking ceil_spec: %s\n", specs->ceil_spec);
	}
}

char	*get_path(char *line, char *new, t_type *type, int k)
{
	int	i;

	i = 0;
	new = allocate_memory(ft_strlen(line), ARRAY, type);
	if (k == 2)
	{
		new[0] = '.';
		new[1] = '/';
	}
	while ((line[i] != 32 || (line[i] >= 9 && line[i] <= 13))
		&& line[i] != '\0')
		i++;
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		&& line[i] != '\0')
		i++;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
			i++;
		else
			new[k++] = line[i++];
	}
	new[k] = '\0';
	return (new);
}
