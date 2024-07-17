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

void	final_map_check(char **array, t_map *map)
{
	int i = 0;
	int k = 0;
	int count = 0;
	int smallest = 2147483647;

	while (array[i] != NULL)
	{
		while (array[i][k] != '\0' && (array[i][k] == 32 || (array[i][k] >= 9
					&& array[i][k] <= 13)))
			k++;
		while (array[i][k] != '\0')
		{
			count++;
			k++;
		}
		if (smallest > count)
			smallest = count;
		k = 0;
		count =0;
		i++;
	}
	printf("smallers %d\n", smallest);
	if (smallest < 3 || i < 3)
		print_and_exit_map("Error: map error1.", map, NULL);
	k = 0;
	while (array[i - 1][k] != '\0' && (array[i - 1][k] == 32 || (array[i
				- 1][k] >= 9 && array[i - 1][k] <= 13)))
		k++;
	while (array[i - 1][k] != '\0')
	{
		if (array[i - 1][k] != '1')
			print_and_exit_map("Error: map error2.", map, NULL);
		k++;
	}
}