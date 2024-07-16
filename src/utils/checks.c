#include "cub3d.h"

void	first_check(int argc, char *argv[])
{
	if (argc != 2)
		exit(1);
	check_map_path(argv[1]);
}

void	check_map_path(char *path)
{
	size_t len;
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		perror("Your map does not have the right extension");
		exit(1);
	}
}