/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:59:47 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 14:01:20 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_line(char *line, t_type *type)
{
	char	*new;
	int		count_trim;
	size_t	i;
	int		len;

	i = 0;
	count_trim = 0;
	len = ft_strlen(line);
	new = allocate_memory(ft_strlen(line), ARRAY, type);
	while ((line[len - 1] == 32 || (line[len - 1] >= 9 && line[len - 1] <= 13))
		|| (line[len - 1] == '\n'))
	{
		count_trim++;
		len--;
	}
	while (i < ft_strlen(line) - count_trim && line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	return (new);
}

void	get_map_parameters(t_map *map, char **array)
{
	int	y;

	y = 0;
	map->map_height = 0;
	map->map_width = 0;
	while (array[map->map_height] != NULL)
	{
		while (array[map->map_height][y] != '\0')
			y++;
		if (y > map->map_width)
			map->map_width = y;
		y = 0;
		map->map_height++;
	}
}
