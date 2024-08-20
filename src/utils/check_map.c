/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:55:29 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 15:20:49 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	final_map_check_dfs(char **array, t_map *map)
{
	int			i;
	int			j;
	t_player	*player;

	player = set_player();
	i = 0;
	j = 0;
	find_player(array, &i, &j, map);
	check_borders(array, i, j, map->check);
	give_player_values(i, j, player);
	map->map2d[i][j] = '0';
}

int	check_borders(char **arr, int i, int j, char **check)
{
	if (i < 0 || j < 0 || (arr[i] == NULL) || j > (int)ft_strlen(arr[i])
		|| (arr[i][j] == '\0') || check[i][j] == 9)
	{
		return (1);
	}
	if (!is_all_good(arr, i, j))
	{
		printf("Error: map has gaps or is not surrounded by 1.\n");
		exit(1);
	}
	check[i][j] = 9;
	check_borders(arr, i - 1, j, check);
	check_borders(arr, i + 1, j, check);
	check_borders(arr, i, j - 1, check);
	check_borders(arr, i, j + 1, check);
	return (0);
}

bool	is_all_good(char **arr, int i, int j)
{
	if (i == 0 && ((arr[i][j] != '1' && !space_check(arr[i][j], 0))))
	{
		printf("Error: map is invalid, %c\n", arr[i][j]);
		return (false);
	}
	if (check_field(arr[i][j]) && i == 0 && (j == 0 || space_check(arr[i][j
				- 1], 0)))
	{
		return (false);
	}
	if (i > 0 && check_field(arr[i][j]) && (space_check(arr[i][j + 1], 1)))
	{
		return (false);
	}
	if (check_field(arr[i][j]) && (arr[i + 1] != NULL && space_check(arr[i
				+ 1][j], 0)))
	{
		return (false);
	}
	if (check_field(arr[i][j]) && (i - 1 >= 0 && space_check(arr[i - 1][j], 0)))
	{
		return (false);
	}
	return (true);
}

bool	check_field(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
	{
		return (true);
	}
	return (false);
}

bool	space_check(char c, int left)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		return (false);
	}
	if (left == 1 && c == '\0')
		return (true);
	else if (left == 0 && (c == 32 || (c >= 9 && c <= 13) || c == '\0'))
	{
		return (true);
	}
	return (false);
}
