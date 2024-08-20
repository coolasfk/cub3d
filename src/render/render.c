/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:29:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 20:19:15 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_cub *cub)
{
	float	angle;
	int		i;

	i = -1;
	angle = cub->player->fc - PI / 4;
	if (angle < 0)
		cub->player->fc += 2 * PI;
	if (angle >= 2 * PI)
		cub->player->fc -= 2 * PI;
	while (++i < SCREEN_W)
	{
		if (angle < 0)
			angle += 2 * PI;
		if (angle >= 2 * PI)
			angle -= 2 * PI;
		launch_rays(cub->player, cub->map, cub->rays, angle);
		update_rays_values(cub->rays, i);
		render_walls(cub->mlx, cub->rays, i, cub->specs);
		angle += FOV / SCREEN_W;
	}
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr, cub->mlx->img,
		0, 0);
	return (0);
}

void	update_rays_values(t_rays *rays, int i)
{
	(void)i;
	if (rays->horizontal_distance > rays->vertical_distance)
	{
		rays->distance_to_wall = rays->vertical_distance;
		rays->wall_direction = rays->wall_direction_v;
		rays->wall_hit = rays->hit_v;
		fix_fisheye(&rays->distance_to_wall, i);
	}
	else
	{
		rays->distance_to_wall = rays->horizontal_distance;
		rays->wall_direction = rays->wall_direction_h;
		rays->wall_hit = rays->hit_h;
		fix_fisheye(&rays->distance_to_wall, i);
	}
}

void	fix_fisheye(float *distance, int i)
{
	float	angle;

	if (i < SCREEN_W / 2)
		i = SCREEN_W / 2 - i;
	else
		i -= SCREEN_W / 2;
	angle = i * FOV / SCREEN_W;
	*distance *= cos(angle);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = mlx->addr[4] + (y * mlx->line_length[4] + x * (mlx->bpp[4] / 8));
	*(unsigned int *)dst = color;
}

void	calc_texture(t_mlx *mlx, t_rays *rays)
{
	if (rays->wall_direction == 'N')
		mlx->texture = NORTH_TEX;
	else if (rays->wall_direction == 'S')
		mlx->texture = SOUTH_TEX;
	else if (rays->wall_direction == 'E')
		mlx->texture = EAST_TEX;
	else if (rays->wall_direction == 'W')
		mlx->texture = WEST_TEX;
	if (mlx->texture != SOUTH_TEX && mlx->texture != WEST_TEX)
		rays->tex_x = (int)((rays->wall_hit - floor(rays->wall_hit))
				* mlx->width[mlx->texture]);
	else
	{
		rays->tex_x = mlx->width[mlx->texture] - ((int)((rays->wall_hit
						- floor(rays->wall_hit)) * mlx->width[mlx->texture]));
	}
	rays->texture_height = mlx->height[mlx->texture];
	rays->tex_y = 0;
}
