#include "cub3d.h"

int	render(t_cub *cub)
{
	t_rays	*rays;
	float	angle;
	int		i;

	i = 0;
	rays = allocate_memory(0, RAYS, &cub->type);
	angle = cub->player->facing - PI / 4;
	while (i < SCREEN_W)
	{
		if (angle < 0)
			angle += 2 * PI;
		if (angle >= 2 * PI)
			angle -= 2 * PI;
		launch_rays(cub->player, cub->map, rays, angle);
		printf("comparing: horizontal: %f, vertical: %f\n",
			rays->horizontal_distance, rays->vertical_distance);
		render_walls(cub->mlx, rays, i);
		// angle += 3 * PI / 180;
		angle += FOV / SCREEN_W * 2;
		printf("wall distance %f\n\n\n", rays->distance_to_wall);
		// i += 30;
		i += 2;
	}
	free(rays);
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr, cub->mlx->img,
		0, 0);
	return (0);
}
/*
Thus to remove the viewing distortion,
	the resulting distance obtained from equations in Figure 17must
	be multiplied by cos(BETA); where BETA is the angle of the ray that
	is being cast relative to the viewing angle. On the figure above,
	the viewing angle (ALPHA) is 90 degrees because the player is facing
	straight upward. Because we have 60 degrees field of view,
	BETA is 30 degrees for the leftmost ray and it is
	-30 degrees for the rightmost ray.*/

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_walls(t_mlx *mlx, t_rays *rays, int x)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;

	wall_height = (int)(PROJ_PLANE_DIST / rays->distance_to_wall);
	draw_start = -wall_height / 2 + SCREEN_H / 2;
	draw_end = wall_height / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	for (int y = draw_start; y < draw_end; y++)
	{
		my_mlx_pixel_put(mlx, x, y, 0xFFFFFF);
	}
	for (int y = draw_end; y < SCREEN_H; y++)
	{
		my_mlx_pixel_put(mlx, x, y, 0x808080);
	}
	for (int y = 0; y < draw_start; y++)
	{
		my_mlx_pixel_put(mlx, x, y, 0x0000FF);
	}
}

void	launch_rays(t_player *player, t_map *map, t_rays *rays, float angle)
{
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	if (angle >= PI + (PI / 2))
	{
		angle = 2 * PI - angle;
		// printf("first quarter\n");
		printf("angle1: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 1);
		horizontal_angle(map, rays, angle, 1);
		if (rays->horizontal_distance > rays->vertical_distance)
			rays->distance_to_wall = rays->vertical_distance;
		else
			rays->distance_to_wall = rays->horizontal_distance;
		rays->distance_to_wall *= cos((PI / 2 - angle) * (PI / 90.0));
	}
	else if (angle < PI / 2)
	{
		// printf("--------------------------------------------------second quarter\n");
		printf("angle2: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 2);
		horizontal_angle(map, rays, angle, 2);
		if (rays->horizontal_distance > rays->vertical_distance)
			rays->distance_to_wall = rays->vertical_distance;
		else
			rays->distance_to_wall = rays->horizontal_distance;
		rays->distance_to_wall *= cos((PI / 2 - angle) * (PI / 90.0));
	}
	else if (angle >= (PI / 2) && angle < PI)
	{
		printf("angle3: %f\n", (angle * 180.0 / PI));
		angle = angle - PI / 2;
		vertical_angle(map, rays, angle, 3);
		horizontal_angle(map, rays, angle, 3);
		// printf("third quarter\n");
	}
	else if (angle >= PI && angle < PI + PI / 2)
	{
		printf("angle4: %f\n", (angle * 180.0 / PI));
		angle = angle - PI;
		vertical_angle(map, rays, angle, 4);
		horizontal_angle(map, rays, angle, 4);
		printf("forth quarter\n");
	}
}

void	vertical_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	char	box;

	// printf("ENTERING: vertical check\n");
	if (angle == 0 || angle == PI / 2 || angle == PI || angle == PI + PI / 2)
	{
		rays->vertical_distance = 3.5;
		return ;
	}
	rays->b = 0.5;
	while (1)
	{
		rays->vertical_distance = rays->b / cos(angle);
		rays->a = sin(angle) * rays->vertical_distance;
		// printf("V--- checking A: %f, B: %f, C: %f\n", rays->a, rays->b,
		// rays->vertical_distance);
		// printf("2V values check: %d y: %d\n", (int)(rays->x + rays->b),
		//(int)(rays->y + rays->a));
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
			{
				rays->horizontal_distance = 2147483647;
				return ;
			}
			// printf("values check x: %f y:%f\n", rays->x, rays->y);
			// printf("1V values check: %d y: %d\n", (int)(rays->x - rays->a),
			//(int)(rays->y + rays->b));
			box = map->map2d[(int)(rays->x - rays->a + 1)][(int)(rays->y
					+ rays->b) + 1];
		}
		else if (quarter == 2)
		{
			if ((int)(rays->x + rays->a) >= map->map_height || (int)(rays->y
					+ rays->b) > map->map_width)
			{
				rays->horizontal_distance = 2147483647;
				return ;
			}
			printf("check x: %f, check y: %f\n", rays->x, rays->y);
			printf("---------------2V values check: x: %d y: %d\n",
				(int)(rays->x + rays->a) + 1, (int)(rays->y + rays->b));
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y + rays->b)
				+ 1];
		}
		else if (quarter == 3)
		{
			box = map->map2d[(int)(rays->x + rays->b)][(int)(rays->y
					- rays->a)];
		}
		else if (quarter == 4)
		{
			box = map->map2d[(int)(rays->x - rays->b)][(int)(rays->y
					- rays->a)];
		}
		if (box == '1')
		{
			// printf("box: %c\n", box);
			// printf("----************************------vertical yes!!!!!!------\n");
			break ;
		}
		rays->b++;
	}
}

void	horizontal_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	char	box;

	rays->a = 0.5;
	if (angle == 0 || angle == PI / 2 || angle == PI || angle == PI + PI / 2)
	{
		rays->horizontal_distance = 3.5;
		return ;
	}
	// printf("ENTERING: horizontal check\n");
	while (1)
	{
		rays->horizontal_distance = rays->a / sin(angle);
		rays->b = cos(angle) * rays->horizontal_distance;
		printf("H--- checking A: %f, B: %f, C: %f\n", rays->a, rays->b,
			rays->horizontal_distance);
		// printf("1H values check: %d y: %d\n", (int)(rays->x - rays->b),
		//(int)(rays->y + rays->a));
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
			{
				rays->horizontal_distance = 2147483647;
				return ;
			}
			// printf("rays->x: %f, rays->y: %f\n", rays->x, rays->y);
			box = map->map2d[(int)(rays->x - rays->a)][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 2)
		{
			if ((int)(rays->x + rays->a) >= map->map_height || (int)(rays->y
					+ rays->b) > map->map_width)
			{
				rays->horizontal_distance = 2147483647;
				return ;
			}
			printf("2h values check: x:%d y: %d\n", ((int)(rays->x + rays->a)+1),
				(int)(rays->y + rays->b));
			printf("original rays->x: %f, rays->y: %f\n", rays->x, rays->y);
			box = map->map2d[(int)(rays->x + rays->a) + 1][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 3)
		{
			box = map->map2d[(int)(rays->x + rays->b)][(int)(rays->y
					- rays->a)];
		}
		else if (quarter == 4)
		{
			box = map->map2d[(int)(rays->x - rays->b)][(int)(rays->y
					- rays->a)];
		}
		if (box == '1')
		{
			// printf("box: %c\n", box);
			// printf("----************************-----horizontal-yes!!!!!!------\n");
			break ;
		}
		rays->a++;
	}
	// printf("exiting horizontal check, rays->c: %f\n",
	// rays->horizontal_distance);
}
/*
void	player_facing_east(t_map *map, t_rays *rays, t_player *player,
		float angle)
{
	float	ray_x;
	float	ray_y;
	float	step_size;
	float	distance_to_wall;

	ray_x = player->player_x;
	ray_y = player->player_y;
	step_size = 0.01;
	distance_to_wall = 0.0;
	while (1)
	{
		ray_x += cos(angle) * step_size;
		ray_y += sin(angle) * step_size;
		distance_to_wall += step_size;
		if (ray_x < 0 || ray_x >= SCREEN_W || ray_y < 0 || ray_y >= SCREEN_H)
		{
			distance_to_wall = SCREEN_W;
			break ;
		}
		if (map->map2d[(int)ray_y][(int)ray_x] == '1')
		{
			break ;
		}
	}
	rays->distance_to_wall = distance_to_wall;
}

void	launch_rays(t_player *player, t_map *map, t_rays *rays, float angle)
{
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	if (angle >= PI + (PI / 2))
	{
		angle = angle - (PI + PI / 2);
		player_facing_east(map, rays, player,
		angle);
	}
	else if (angle < PI / 2)
	{
		player_facing_east(map, rays, player,
		angle);
	}
	else if (angle >= (PI / 2) && angle < PI)
	{
		player_facing_east(map, rays, player,
		angle);
	}
	else if (angle >= PI && angle < PI + PI / 2)
	{
		player_facing_east(map, rays, player,
		angle);
	}
}
*/