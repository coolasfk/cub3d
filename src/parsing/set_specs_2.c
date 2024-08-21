/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:07:09 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/21 12:58:05 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	fd = 0;
	if (!specs->n_spec || !specs->s_spec || !specs->e_spec || !specs->w_spec
		|| !specs->ceil_spec || !specs->floor_spec)
	{
		printf("Error: some of the specifications are missing2.\n");
		exit(1);
	}
	fd = open(specs->n_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the north tex file.", specs);
	fd = open(specs->s_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the south tex file.", specs);
	fd = open(specs->e_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the east tex.", specs);
	fd = open(specs->w_spec, O_RDONLY);
	if (fd < 0)
		print_and_exit_specs("Error: cannot open the west tex.", specs);
}

void	get_rgb(char **str, t_rgb **rgb, t_type *type, t_specs *specs)
{
	int		i;
	char	temp[4];
	t_rgb	*current;

	i = 0;
	specs->ptr = NULL;
	while ((*str)[i] != '\0')
	{
		specs->k = 0;
		current = allocate_memory(0, RGB, type);
		while ((*str)[i] != ',' && !((*str)[i] >= 9 && (*str)[i] <= 13)
			&& (*str)[i] != '\0')
			temp[specs->k++] = (*str)[i++];
		temp[specs->k] = '\0';
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
}

int	rgb_check(char *rgb, t_specs *specs)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (rgb[i] != '\0')
		i++;
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
