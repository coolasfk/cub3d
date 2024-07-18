#include "cub3d.h"

void	first_check(int argc, char *argv[])
{
	if (argc != 2)
		exit(1);
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
	int i = 0;
	int j = 0;
	int count = 0;
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
	printf("number of players %d\n", count);
	if (count != 1)
		print_and_exit_map("Error: wrong number of players.", map, NULL);
}