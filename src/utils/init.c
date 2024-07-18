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
	return (cub);
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

t_player	*set_player(void)
{
	t_type			*type;
	static t_player	*player;

	type = NULL;
	if (player)
		return (player);
	player = allocate_memory(0, PLAYER, type);
    player->facing = 666;
	return (player);
}

t_player	*get_player(void)
{
	static t_player	*player;

	if (!player)
		player = get_player();
	return (player);
}
