#include "cub3d.h"

t_cub	*set_cub(void)
{
	static t_cub	*cub;
	t_type			*type;

	if (cub)
		return (cub);
	type = NULL;
	cub = allocate_memory(0, CUB, type);
	cub->specs = NULL;
	cub->map = NULL;
	cub->player = NULL;
    return cub;
}

t_cub	*get_cub(void)
{
	static t_cub	*cub;

	if (!cub)
	{
		cub = set_cub();
	}
	return (cub);
}
