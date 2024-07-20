#include "cub3d.h"

void	*allocate_memory(int size, int alloc_type, t_type *ret)
{
	if (alloc_type == SPECS)
		ret = malloc(sizeof(t_specs));
	else if (alloc_type == ARRAY)
		ret = malloc(sizeof(char) * size + 1);
	else if (alloc_type == MAP)
		ret = malloc(sizeof(t_map));
	else if (alloc_type == ARRAY2D)
		ret = malloc(sizeof(char *) * size);
    else if (alloc_type == CUB)
		ret = malloc(sizeof(t_cub));
	else if (alloc_type == RGB)
		ret = malloc(sizeof(t_rgb));
	else if (alloc_type == PLAYER)
		ret = malloc(sizeof(t_player));
	else if (alloc_type == MLX)
		ret = malloc(sizeof(t_mlx));
	if (!ret)
	{
		perror("Cannot allocate memory");
		exit(1);
	}
	return (ret);
}