#include "cub3d.h"

void	final_map_check(char **array, t_map *map)
{
	int	i;
	int	j;

	find_player(array, &i, &j, map);
	check_borders(array, i, j, *array);
}

int	check_borders(char **arr, int i, int j, char *check)
{
	if (check[i][j] = 0 && i == 0 && j >= 0 && arr[i][j] == '0'
		&& space_check(arr[i + 1][j]))
	{
		printf("error deceted\n");
		return (0);
	}
	check[i][j] = 1;
	check_borders(arr, i - 1, j, map);
	check_borders(arr, i + 1, j, map);
	check_borders(arr, i, j + 1, map);
	check_borders(arr, i, j - 1, map);
	return (1);
}

int	space_check(char c)
{
	if (c == 32 || c >= 9 && c <= 13)
		return (1);
	return (0);
}

void	find_player(char **array, int *i, int *j, t_map *map)
{
	t_player *player;
	player = set_player();
	while (array[i] != NULL)
	{
		while (array[i][j] != '\0')
		{
			if (array[i][j] == 'N')
				player->facing = 0;
			else if (array[i][j] == 'W')
				player->facing = 270;
			else if (array[i][j] == 'E')
				player->facing = 90;
			else if (array[i][j] == 'S')
				player->facing = 180;
			if (player->facing != NULL)
				return ;
			j++;
		}
		j = 0;
		i++;
	}
	print_and_exit_map("Error: player not found.", map, NULL)
}