/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:29:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 14:28:00 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_cub *cub)
{
	float	angle;
	int		i;

	i = -1;
	angle = cub->player->facing - PI / 4;
	if (angle < 0)
		cub->player->facing += 2 * PI;
	if (angle >= 2 * PI)
		cub->player->facing -= 2 * PI;
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

void	start_variables(t_rays *rays, int x)
{
	rays->wall_height = (int)(PLANE / rays->distance_to_wall * 2.3);
	(void)x;
	rays->draw_start = -rays->wall_height / 2 + SCREEN_H / 2;
	rays->draw_end = rays->wall_height / 2 + SCREEN_H / 2;
	if (rays->draw_start < 0)
		rays->draw_start = 0;
	if (rays->draw_end >= SCREEN_H)
		rays->draw_end = SCREEN_H - 1;
}

void	render_walls(t_mlx *mlx, t_rays *rays, int x, t_specs *specs)
{
	int		y;
	char	*pixel;
	int		d;

	start_variables(rays, x);
	calc_texture(mlx, rays);
	y = rays->draw_start - 1;
	while (++y < rays->draw_end)
	{
		d = (y - SCREEN_H / 2 + rays->wall_height / 2) * rays->texture_height;
		rays->tex_y = d / rays->wall_height;
		pixel = mlx->addr[mlx->texture] + ((int)(rays->tex_y)
				* mlx->line_length[mlx->texture] + rays->tex_x
				* (mlx->bpp[mlx->texture] / 8));
		my_mlx_pixel_put(mlx, x, y, *(unsigned int *)pixel);
	}
	y = rays->draw_end - 1;
	while (++y < SCREEN_H)
		my_mlx_pixel_put(mlx, x, y, specs->floor_color);
	y = -1;
	while (++y < rays->draw_start)
		my_mlx_pixel_put(mlx, x, y, specs->ceil_color);
}

void	launch_rays(t_player *player, t_map *map, t_rays *rays, float angle)
{
	rays->x = player->player_x;
	rays->y = player->player_y;
	if (angle >= PI + (PI / 2))
	{
		angle = 2 * PI - angle;
		vertical_angle(map, rays, angle, 1);
		horizontal_angle(map, rays, angle, 1);
	}
	else if (angle < PI / 2)
	{
		vertical_angle(map, rays, angle, 2);
		horizontal_angle(map, rays, angle, 2);
	}
	else if (angle >= (PI / 2) && angle < PI)
	{
		angle = PI - angle;
		vertical_angle(map, rays, angle, 3);
		horizontal_angle(map, rays, angle, 3);
	}
	else if (angle >= PI && angle < PI + PI / 2)
	{
		angle = angle - PI;
		vertical_angle(map, rays, angle, 4);
		horizontal_angle(map, rays, angle, 4);
	}
}

void	check_box_v(t_rays *rays, t_map *map, int quarter)
{
	if (quarter == 1)
	{
		rays->hit_v = rays->y - rays->a;
		rays->box = map->map2d[(int)(rays->hit_v)][(int)(rays->x + rays->b)];
	}
	else if (quarter == 2)
	{
		rays->hit_v = rays->y + rays->a;
		rays->box = map->map2d[(int)(rays->hit_v)][(int)(rays->x + rays->b)];
	}
	else if (quarter == 3)
	{
		rays->hit_v = rays->y + rays->a;
		rays->box = map->map2d[(int)(rays->hit_v)][(int)(rays->x - rays->b
				- 1)];
	}
	else if (quarter == 4)
	{
		rays->hit_v = rays->y - rays->a;
		rays->box = map->map2d[(int)(rays->hit_v)][(int)(rays->x - rays->b
				- 1)];
	}
}

void	vertical_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	if (quarter == 3 || quarter == 4)
		rays->wall_direction_v = 'W';
	else
		rays->wall_direction_v = 'E';
	if (fabs(angle) < EPSILON || fabs(angle - M_PI_2) < EPSILON || fabs(angle
			- M_PI) < EPSILON || fabs(angle - (3 * M_PI_2)) < EPSILON)
		return ;
	rays->b = 0.5;
	while (1)
	{
		rays->vertical_distance = rays->b / cos(angle);
		rays->a = sin(angle) * rays->vertical_distance;
		if ((quarter == 1 && (((int)(rays->y - rays->a) < 0 || (int)(rays->x
							+ rays->b) > map->map_width))) || (quarter == 2
				&& ((int)(rays->y + rays->a) >= map->map_height || (int)(rays->x
						+ rays->b) > map->map_width)) || (quarter == 3
				&& ((int)(rays->y + rays->a) >= map->map_height || (int)(rays->x
						- rays->b - 1) < 0)) || (quarter == 4 && ((int)(rays->y
						- rays->a) < 0 || (int)(rays->x - rays->b - 1) < 0)))
			return ;
		check_box_v(rays, map, quarter);
		if (rays->box == '1')
			break ;
		rays->b++;
	}
}
void	check_box_h(t_rays *rays, t_map *map, int quarter)
{
	if (quarter == 1)
	{
		rays->hit_h = rays->x + rays->b;
		rays->box = map->map2d[(int)(rays->y - rays->a
				- 1)][(int)(rays->hit_h)];
	}
	else if (quarter == 2)
	{
		rays->hit_h = rays->x + rays->b;
		rays->box = map->map2d[(int)(rays->y + rays->a)][(int)(rays->hit_h)];
	}
	else if (quarter == 3)
	{
		rays->hit_h = rays->x - rays->b;
		rays->box = map->map2d[(int)(rays->y + rays->a)][(int)(rays->hit_h)];
	}
	else if (quarter == 4)
	{
		rays->hit_h = rays->x - rays->b;
		rays->box = map->map2d[(int)(rays->y - rays->a
				- 1)][(int)(rays->hit_h)];
	}
}

void	horizontal_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	if (quarter == 1 || quarter == 4)
		rays->wall_direction_h = 'N';
	else
		rays->wall_direction_h = 'S';
	rays->a = -0.5;
	if (fabs(angle) < EPSILON || fabs(angle - M_PI_2) < EPSILON || fabs(angle
			- M_PI) < EPSILON || fabs(angle - (3 * M_PI_2)) < EPSILON)
		return ;
	while (++rays->a > 0)
	{
		rays->horizontal_distance = rays->a / sin(angle);
		rays->b = cos(angle) * rays->horizontal_distance;
		if ((quarter == 1 && ((int)(rays->y - rays->a - 1) < 0 || (int)(rays->x
						+ rays->b) > map->map_width)) || (quarter == 2
				&& ((int)(rays->y + rays->a) >= map->map_height || (int)(rays->x
						+ rays->b) > map->map_width)) || (quarter == 3
				&& ((int)(rays->y + rays->a) > map->map_height || (int)(rays->x
						- rays->b) < 0)) || (quarter == 4 && ((int)(rays->y
						- rays->a - 1) < 0 || (int)(rays->x
						- rays->b) > map->map_width)))
			return ;
		check_box_h(rays, map, quarter);
		if (rays->box == '1')
			break ;
	}
}
