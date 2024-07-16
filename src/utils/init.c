#include "cub3d.h"

void	init(t_cub *cub)
{
    t_type *type;
    type = NULL;
    cub = allocate_memory(0, CUB, type);
	cub->specs = NULL;
	cub->map = NULL;
	cub->player = NULL;
}