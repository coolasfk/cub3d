/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:28:35 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 20:19:01 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player->fc -= FOV / SCREEN_W * 100;
	if (keycode == KEY_RIGHT)
		cub->player->fc += FOV / SCREEN_W * 100;
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
