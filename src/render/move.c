/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:28:35 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 14:58:38 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_forward(t_cub *cub)
{
	if (cub->player->facing >= PI + PI / 4 && cub->player->facing < PI + 3 * PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				- 1)][(int)cub->player->player_x] == '0')
			cub->player->player_y -= 1;
	}
	else if (cub->player->facing >= PI + 3 * PI / 4 || cub->player->facing < PI
		/ 4)
	{
		if (cub->map->map2d[(int)cub->player->player_y][(int)
		(cub->player->player_x + 1)] == '0')
			cub->player->player_x += 1;
	}
	else if (cub->player->facing >= PI / 4 && cub->player->facing < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				+ 1)][(int)cub->player->player_x] == '0')
			cub->player->player_y += 1;
	}
	else if (cub->player->facing >= 3 * PI / 4 && cub->player->facing 
	< PI + PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)(cub->player->player_x
				- 1)] == '0')
			cub->player->player_x -= 1;
	}
}

void	move_player_left(t_cub *cub)
{
	if (cub->player->facing >= PI + PI / 4 && cub->player->facing < PI + 3 * PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)cub->player->player_x
			- 1] == '0')
			cub->player->player_x -= 1;
	}
	else if (cub->player->facing >= PI + 3 * PI / 4 || cub->player->facing < PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				- 1)][(int)(cub->player->player_x)] == '0')
			cub->player->player_y -= 1;
	}
	else if (cub->player->facing >= PI / 4 && cub->player->facing < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)cub->player->player_x
			+ 1] == '0')
			cub->player->player_x += 1;
	}
	else if (cub->player->facing >= 3 * PI / 4 && cub->player->facing < PI + PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				+ 1)][(int)(cub->player->player_x)] == '0')
			cub->player->player_y += 1;
	}
}

void	move_player_backward(t_cub *cub)
{
	if (cub->player->facing >= PI + PI / 4 && cub->player->facing < PI + 3 * PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				+ 1)][(int)cub->player->player_x] == '0')
			cub->player->player_y += 1;
	}
	else if (cub->player->facing >= PI + 3 * PI / 4 || cub->player->facing < PI
		/ 4)
	{
		if (cub->map->map2d[(int)cub->player->player_y][(int)(cub->player->player_x
				- 1)] == '0')
			cub->player->player_x -= 1;
	}
	else if (cub->player->facing >= PI / 4 && cub->player->facing < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				- 1)][(int)cub->player->player_x] == '0')
			cub->player->player_y -= 1;
	}
	else if (cub->player->facing >= 3 * PI / 4 && cub->player->facing < PI + PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)(cub->player->player_x
				+ 1)] == '0')
			cub->player->player_x += 1;
	}
}

void	move_player_right(t_cub *cub)
{
	if (cub->player->facing >= PI + PI / 4 && cub->player->facing < PI + 3 * PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)cub->player->player_x
			+ 1] == '0')
			cub->player->player_x += 1;
	}
	else if (cub->player->facing >= PI + 3 * PI / 4 || cub->player->facing < PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				+ 1)][(int)(cub->player->player_x)] == '0')
			cub->player->player_y += 1;
	}
	else if (cub->player->facing >= PI / 4 && cub->player->facing < 3 * PI / 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y)][(int)cub->player->player_x
			- 1] == '0')
			cub->player->player_x -= 1;
	}
	else if (cub->player->facing >= 3 * PI / 4 && cub->player->facing < PI + PI
		/ 4)
	{
		if (cub->map->map2d[(int)(cub->player->player_y
				- 1)][(int)(cub->player->player_x)] == '0')
			cub->player->player_y -= 1;
	}
}

void	rotate_player(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player->facing -= FOV / SCREEN_W * 100;
	else if (keycode == KEY_RIGHT)
		cub->player->facing += FOV / SCREEN_W * 100;
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_player_forward(cub);
	else if (keycode == KEY_A)
		move_player_left(cub);
	else if (keycode == KEY_S)
		move_player_backward(cub);
	else if (keycode == KEY_D)
		move_player_right(cub);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(keycode, cub);
	else if (keycode == 53)
		end_game(cub);
	render(cub);
	return (0);
}
