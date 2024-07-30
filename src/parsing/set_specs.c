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
	check_specs(specs);
	change_rgb_to_hex(&specs->floor_color, specs->floor);
	change_rgb_to_hex(&specs->ceil_color, specs->ceil);
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
	char		*line;
	int			fd;
	static int	flag;

	flag = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the file.", specs);
	line = get_next_line(fd);
	while (line)
	{
		check_line(line, specs, type);
		check_line2(line, specs, &flag);
		free(line);
		line = get_next_line(fd);
		specs->rows++;
	}
	free(line);
	printf("check specs rows %d\n", specs->rows);
}

void	check_line2(char *line, t_specs *specs, int *flag)
{
	int	i;

	i = 0;
	printf("-------flag is : %d\n", *flag);
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13) || line[i] == '\n')
		&& line[i] != '\0')
		i++;
	if (*flag == 0 && line[i] == '1')
		*flag = 1;
	if (*flag == 1 && (line[i] != '1') && (line[i] != '\n')
		&& (line[i] != '\0'))
	{
		printf("line[i] check%c\n", line[i]);
		print_and_exit_specs("Error: map error 3.", specs);
	}
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
		get_rgb(&specs->floor_spec, &specs->floor, type, specs);
	}
	else if (line[i] == 'C' && line[i + 1] == 32)
	{
		specs->ceil_spec = get_path(line, specs->ceil_spec, type, 0);
		get_rgb(&specs->ceil_spec, &specs->ceil, type, specs);
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

void	check_specs(t_specs *specs)
{
	int	fd;

	/*
	to be switched on later!!!!! */
	fd = 0;
	if (!specs->n_spec || !specs->s_spec || !specs->e_spec || !specs->w_spec
		|| !specs->ceil_spec || !specs->floor_spec)
	{
		printf("Error: some of the specifications are missing2.\n");
		exit(1);
	}
	// turn THIS back on once you have valid textures!!!!!!!!!
	/**/
	fd = open(specs->n_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the file1.", specs);
	fd = open(specs->s_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the file2.", specs);
	fd = open(specs->e_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the file3.", specs);
	fd = open(specs->w_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the file4.", specs);
}

void	get_rgb(char **str, t_rgb **rgb, t_type *type, t_specs *specs)
{
	int		i;
	int		k;
	char	temp[4];
	t_rgb	*current;

	i = 0;
	specs->ptr = NULL;
	printf("179 check\n");
	while ((*str)[i] != '\0')
	{
		printf("182 check\n");
		k = 0;
		current = allocate_memory(0, RGB, type);
		while ((*str)[i] != ',' && !((*str)[i] >= 9 && (*str)[i] <= 13)
			&& (*str)[i] != '\0')
			temp[k++] = (*str)[i++];
		temp[k] = '\0';
		rgb_check(temp, specs);
		current->value = ft_atoi(temp);
		current->next = NULL;
		if (*rgb == NULL)
			*rgb = current;
		else
			specs->ptr->next = current;
		specs->ptr = current;
		while ((*str)[i] == ',' || ((*str)[i] >= 9 && (*str)[i] <= 13))
			i++;
	}
	printf("199 check\n");
	/*
	*str = allocate_memory(10, ARRAY, type);
	change_rgb_to_hex(specs, *rgb, str);*/
	printf("--------str check: %s\n", *str);
}

int	rgb_check(char *rgb, t_specs *specs)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (rgb[i] != '\0')
		i++;
	printf("rgb check : %s i : %d, \n", rgb, i);
	if (i == 0 || i > 3 || (i == 1 && (rgb[0] < '0' || rgb[0] > '9')) || (i == 2
			&& (rgb[0] < '0' || rgb[0] > '9' || rgb[1] < '0' || rgb[1] > '9'))
		|| (i == 3 && rgb[0] == '1' && (rgb[1] < '0' || rgb[1] > '9'
				|| rgb[2] < '0' || rgb[2] > '9')) || (i == 3 && rgb[0] == '2'
			&& ((rgb[1] < '0' || rgb[1] > '5') || (rgb[2] < '0'
					|| rgb[2] > '9'))) || (i == 3 && rgb[0] == '2'
			&& rgb[1] == '5' && (rgb[2] < '0' || rgb[2] > '5')) || (i == 3
			&& rgb[0] > '2'))
		ret = 1;
	if (ret == 1)
		print_and_exit_specs("Error: wrong RGB values.", specs);
	return (0);
}
