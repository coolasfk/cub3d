/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:20:58 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 15:21:00 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*set_cub(char *argv[])
{
	static t_cub	*cub;
	t_type			*type;

	if (cub)
		return (cub);
	type = NULL;
	cub = allocate_memory(0, CUB, type);
	cub->mlx = allocate_memory(0, MLX, type);
	cub->rays = allocate_memory(0, RAYS, &cub->type);
	cub->specs = set_specs(argv[1]);
	cub->map = set_map(argv[1]);
	cub->player = get_player();
	return (cub);
}

t_cub	*get_cub(void)
{
	static t_cub	*cub;

	if (!cub)
	{
		cub = set_cub(NULL);
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
	player->fc = -1;
	return (player);
}

t_player	*get_player(void)
{
	static t_player	*player;

	if (!player)
		player = set_player();
	return (player);
}

void	give_player_values(int i, int j, t_player *player)
{
	player->plr_y = i + 0.5;
	player->plr_x = j + 0.5;
}
