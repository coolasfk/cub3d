/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:34:03 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/21 12:50:14 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_check(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Error: Wrong number of arguments.\n");
		exit(1);
	}	
	check_map_path(argv[1]);
}

void	check_map_path(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		perror("Your map does not have the right extension");
		exit(1);
	}
}

void	check_players(char **array, t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (array[i] != NULL)
	{
		while (array[i][j] != '\0')
		{
			if (array[i][j] == 'N' || array[i][j] == 'W' || array[i][j] == 'E'
				|| array[i][j] == 'S')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count != 1)
		print_and_exit_map("Error: wrong number of players.", map, NULL);
}

void	find_player(char **array, int *i, int *j, t_map *map)
{
	t_player	*player;

	player = get_player();
	while (array[*i] != NULL)
	{
		while (array[*i][*j] != '\0')
		{
			if (array[*i][*j] == 'E')
				player->fc = 0;
			else if (array[*i][*j] == 'N')
				player->fc = PI + (PI / 2);
			else if (array[*i][*j] == 'S')
				player->fc = PI / 2;
			else if (array[*i][*j] == 'W')
				player->fc = PI;
			if (player->fc != -1)
				return ;
			(*j)++;
		}
		*j = 0;
		(*i)++;
	}
	print_and_exit_map("Error: player not found.", map, NULL);
}
