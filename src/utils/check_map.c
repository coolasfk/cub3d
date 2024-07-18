#include "cub3d.h"

void	final_map_check_dfs(char **array, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	find_player(array, &i, &j, map);
	check_borders(array, i, j, map->check);
}
int	check_borders(char **arr, int i, int j, char **check)
{
	int	up;
	int	down;
	int	left;
	int	right;

	// If out of bounds or already checked
	if (i < 0 || j < 0 || (arr[i] == NULL || arr[i][j] == '\0')
		|| check[i][j] == 9)
	{
		return (1); // Out of bounds or already checked is not an error
	}
	if (!is_all_good(arr, i, j))
	{
		printf("Error: map has gaps or is not surrounded by 1\n");
		exit(1);
	}
	// Mark the cell as checked
	check[i][j] = 9;
	// Recursively visit all adjacent cells (up, down, left, right)
	up = check_borders(arr, i - 1, j, check);
	down = check_borders(arr, i + 1, j, check);
	left = check_borders(arr, i, j - 1, check);
	right = check_borders(arr, i, j + 1, check);
	return (up && down && left && right);
}

bool	is_all_good(char **arr, int i, int j)
{
	if (check_field(arr[i][j])&&i  == 0 && (j == 0 || space_check(arr[i][j
				- 1])))
	{
		return (false);
	}
	if (i > 0 && check_field(arr[i][j]) && (space_check(arr[i][j + 1])))
	{
		return (false);
	}
	if (check_field(arr[i][j]) && (arr[i + 1] != NULL && space_check(arr[i
				+ 1][j])))
	{
		return (false);
	}
	if (check_field(arr[i][j]) && (arr[i - 1] != NULL && space_check(arr[i
				- 1][j])))
	{
		return (false);
	}
	return (true);
}
// Function to check if a cell is adjacent to an empty space
bool	check_field(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
	{
		return (true);
	}
	return (false);
}
bool	space_check(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		return (false);
	}
	if (c == 32 || (c >= 9 && c <= 13) || c == '\0')
	{
		return (true);
	}
	return (false);
}

void	find_player(char **array, int *i, int *j, t_map *map)
{
	t_player *player;
	player = set_player();
	while (array[*i] != NULL)
	{
		while (array[*i][*j] != '\0')
		{
			if (array[*i][*j] == 'N')
				player->facing = 0;
			else if (array[*i][*j] == 'W')
				player->facing = 270;
			else if (array[*i][*j] == 'E')
				player->facing = 90;
			else if (array[*i][*j] == 'S')
				player->facing = 180;
			if (player->facing != 666)
            

                return ;
            
				
			(*j)++;
		}
		*j = 0;
		(*i)++;
	}
	print_and_exit_map("Error: player not found.", map, NULL);
}