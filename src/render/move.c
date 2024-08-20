/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:28:35 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 15:12:58 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_forward(t_cub *cub)
{
	if (cub->player->fc >= PI + PI / 4 && cub->player->fc < PI + 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				- 1)][(int)cub->player->plr_x] == '0')
			cub->player->plr_y -= 1;
	}
	else if (cub->player->fc >= PI + 3 * PI / 4 || cub->player->fc < PI / 4)
	{
		if (cub->map->map2d[(int)cub->player->plr_y][(int)(cub->player->plr_x
			+ 1)] == '0')
			cub->player->plr_x += 1;
	}
	else if (cub->player->fc >= PI / 4 && cub->player->fc < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				+ 1)][(int)cub->player->plr_x] == '0')
			cub->player->plr_y += 1;
	}
	else if (cub->player->fc >= 3 * PI / 4 && cub->player->fc < PI + PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)(cub->player->plr_x
				- 1)] == '0')
			cub->player->plr_x -= 1;
	}
}

void	move_player_left(t_cub *cub)
{
	if (cub->player->fc >= PI + PI / 4 && cub->player->fc < PI + 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)cub->player->plr_x
			- 1] == '0')
			cub->player->plr_x -= 1;
	}
	else if (cub->player->fc >= PI + 3 * PI / 4 || cub->player->fc < PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				- 1)][(int)(cub->player->plr_x)] == '0')
			cub->player->plr_y -= 1;
	}
	else if (cub->player->fc >= PI / 4 && cub->player->fc < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)cub->player->plr_x
			+ 1] == '0')
			cub->player->plr_x += 1;
	}
	else if (cub->player->fc >= 3 * PI / 4 && cub->player->fc < PI + PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				+ 1)][(int)(cub->player->plr_x)] == '0')
			cub->player->plr_y += 1;
	}
}

void	move_player_backward(t_cub *cub)
{
	if (cub->player->fc >= PI + PI / 4 && cub->player->fc < PI + 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				+ 1)][(int)cub->player->plr_x] == '0')
			cub->player->plr_y += 1;
	}
	else if (cub->player->fc >= PI + 3 * PI / 4 || cub->player->fc < PI / 4)
	{
		if (cub->map->map2d[(int)cub->player->plr_y][(int)(cub->player->plr_x
			- 1)] == '0')
			cub->player->plr_x -= 1;
	}
	else if (cub->player->fc >= PI / 4 && cub->player->fc < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				- 1)][(int)cub->player->plr_x] == '0')
			cub->player->plr_y -= 1;
	}
	else if (cub->player->fc >= 3 * PI / 4 && cub->player->fc < PI + PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)(cub->player->plr_x
				+ 1)] == '0')
			cub->player->plr_x += 1;
	}
}

void	move_player_right(t_cub *cub)
{
	if (cub->player->fc >= PI + PI / 4 && cub->player->fc < PI + 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)cub->player->plr_x
			+ 1] == '0')
			cub->player->plr_x += 1;
	}
	else if (cub->player->fc >= PI + 3 * PI / 4 || cub->player->fc < PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				+ 1)][(int)(cub->player->plr_x)] == '0')
			cub->player->plr_y += 1;
	}
	else if (cub->player->fc >= PI / 4 && cub->player->fc < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y)][(int)cub->player->plr_x
			- 1] == '0')
			cub->player->plr_x -= 1;
	}
	else if (cub->player->fc >= 3 * PI / 4 && cub->player->fc < PI + PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->plr_y
				- 1)][(int)(cub->player->plr_x)] == '0')
			cub->player->plr_y -= 1;
	}
}
