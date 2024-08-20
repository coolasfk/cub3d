/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:07:09 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 14:13:04 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13) || line[i] == '\n')
		&& line[i] != '\0')
		i++;
	if (*flag == 0 && line[i] == '1')
		*flag = 1;
	if (*flag == 1 && (line[i] != '1') && (line[i] != '\n')
		&& (line[i] != '\0'))
		print_and_exit_specs("Error: map error 3.", specs);
}

void	check_line(char *line, t_specs *specs, t_type *type)
{
	int	i;

	i = 0;
	while ((line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		&& line[i] != '\0')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		specs->n_spec = get_path(line, specs->n_spec, type, 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		specs->s_spec = get_path(line, specs->s_spec, type, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		specs->w_spec = get_path(line, specs->w_spec, type, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		specs->e_spec = get_path(line, specs->e_spec, type, 2);
	else if (line[i] == 'F' && line[i + 1] == 32)
	{
		specs->floor_spec = get_path(line, specs->floor_spec, type, 0);
		get_rgb(&specs->floor_spec, &specs->floor, type, specs);
	}
	else if (line[i] == 'C' && line[i + 1] == 32)
	{
		specs->ceil_spec = get_path(line, specs->ceil_spec, type, 0);
		get_rgb(&specs->ceil_spec, &specs->ceil, type, specs);
	}
}
