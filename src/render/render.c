#include "cub3d.h"

int	render(t_cub *cub)
{
	float	angle;
	int		i;

	i = 0;
	angle = cub->player->facing;
	if (angle < 0)
		cub->player->facing += 2 * PI;
	if (angle >= 2 * PI)
		cub->player->facing -= 2 * PI;
	while (i < SCREEN_W)
	{
		if (angle < 0)
			angle += 2 * PI;
		if (angle >= 2 * PI)
			angle -= 2 * PI;
		// printf("------angle render  check %f\n", angle * 180 / PI);
		launch_rays(cub->player, cub->map, cub->rays, angle);
		// printf("comparing: horizontal: %f, vertical: %f\n",
		// rays->horizontal_distance, rays->vertical_distance);
		if (cub->rays->horizontal_distance > cub->rays->vertical_distance)
			cub->rays->distance_to_wall = cub->rays->vertical_distance;
		else
			cub->rays->distance_to_wall = cub->rays->horizontal_distance;
		// rays->distance_to_wall *= cos(angle);
		fix_fisheye(&cub->rays->distance_to_wall, i);
		render_walls(cub->mlx, cub->rays, i, cub->specs);
		// angle += 2 * PI / 180;
		// angle += FOV / SCREEN_W * 4;
		angle += FOV / SCREEN_W;
		// printf("wall distance %f\n\n\n", rays->distance_to_wall);
		// i += 30;
		// i += 4;
		i++;
	}
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr, cub->mlx->img,
		0, 0);
	return (0);
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
	dst = mlx->addr[4] + (y * mlx->line_length[4] + x
			* (mlx->bpp[4] / 8));
	*(unsigned int *)dst = color;
}

void	render_walls(t_mlx *mlx, t_rays *rays, int x, t_specs *specs)
{
	int				wall_height;
	int				draw_start;
	int				draw_end;
	int			y;
	char			*pixel;
	int				tex_x;
	int tex_y;

	wall_height = (int)(PROJ_PLANE_DIST / rays->distance_to_wall);
	draw_start = -wall_height / 2 + SCREEN_H / 2;
	draw_end = wall_height / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	y = draw_start;
	printf("wall_height %d\n", wall_height);
	tex_x = x;
	tex_y = 0;
	while (y < draw_end)
	{
		if (rays->wall_direction == 'N')
		{
			mlx->texture = NORTH_TEX;
		}
		else if (rays->wall_direction == 'S')
		{
			mlx->texture = SOUTH_TEX;
		}
		else if (rays->wall_direction == 'E')
		{
			mlx->texture = EAST_TEX;
		}
		else if (rays->wall_direction == 'W')
		{
			mlx->texture = WEST_TEX;
		}
	
		if (tex_x > 100)
			tex_x = x % 100;
		if (tex_y > 100)
			tex_y = 0;
		pixel = mlx->addr[mlx->texture] + ((int)(tex_y *(mlx->line_length[mlx->texture]))
			+ tex_x * (mlx->bpp[mlx->texture] / 8));
		my_mlx_pixel_put(mlx, x, y, *(unsigned int *)pixel);
		tex_y++;
		y++;
	}
	y = draw_end;
	while (y < SCREEN_H)
	{
		mlx->texture = IMG;
		my_mlx_pixel_put(mlx, x, y, specs->floor_color);
		y++;
	}
	y = 0;
	while (y < draw_start)
	{
		mlx->texture = IMG;
		my_mlx_pixel_put(mlx, x, y, specs->ceil_color);
		y++;
	}
}
void	launch_rays(t_player *player, t_map *map, t_rays *rays, float angle)
{
	// print2d_array(map->map2d);
	rays->x = player->player_x;
	rays->y = player->player_y;
	if (angle >= PI + (PI / 2))
	{
		angle = 2 * PI - angle;
		// printf("angle1: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 1);
		horizontal_angle(map, rays, angle, 1);
	}
	else if (angle < PI / 2)
	{
		// printf("angle2: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 2);
		horizontal_angle(map, rays, angle, 2);
	}
	else if (angle >= (PI / 2) && angle < PI)
	{
		angle = PI - angle;
		// printf("angle3: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 3);
		horizontal_angle(map, rays, angle, 3);
	}
	else if (angle >= PI && angle < PI + PI / 2)
	{
		angle = angle - PI;
		// printf("angle4: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 4);
		horizontal_angle(map, rays, angle, 4);
	}
}

void	vertical_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	char	box;

	// printf("ENTERING: vertical check\n");
	if (fabs(angle) < EPSILON || fabs(angle - M_PI_2) < EPSILON || fabs(angle
			- M_PI) < EPSILON || fabs(angle - (3 * M_PI_2)) < EPSILON)
	{
		rays->vertical_distance = rays->vertical_distance;
		return ;
	}
	rays->b = 0.5;
	while (1)
	{
		rays->vertical_distance = rays->b / cos(angle);
		rays->a = sin(angle) * rays->vertical_distance;
		/*printf("Vertical: /\\- A: %f, B: %f, C: %f\n", rays->a, rays->b,
			rays->vertical_distance);*/
		// printf("2V values check: %d y: %d\n", (int)(rays->x + rays->b),
		//(int)(rays->y + rays->a));
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
				return ;
			rays->wall_direction = 'E';
			// printf("values check  original X: %d Y:%d\n", (int)rays->x,
			//(int)rays->y);
			/*printf("1V values check: +++++ %d y: %d\n", (int)(rays->x
					- rays->a), (int)(rays->y + rays->b));*/
			box = map->map2d[(int)(rays->x - rays->a)][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 2)
		{
			if ((int)(rays->x + rays->a) >= map->map_height || (int)(rays->y
					+ rays->b) > map->map_width)
				return ;
			rays->wall_direction = 'E';
			// printf("check x: %f, check y: %f\n", rays->x, rays->y);
			// printf("---------------im checking the field: x: %d y: %d\n",
			//(int)(rays->x + rays->a), (int)(rays->y + rays->b) + 1);
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 3)
		{
			if ((int)(rays->x + rays->a) >= map->map_height || (int)(rays->y
					- rays->b - 1) < 0)
				return ;
			rays->wall_direction = 'W';
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y - rays->b
					- 1)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y - rays->b
					- 1) < 0)
				return ;
			rays->wall_direction = 'W';
			// printf("-vetical--------------im checking the field: x: %d y:
			//%d\n",
			//(int)(rays->x - rays->a), (int)(rays->y - rays->b - 1) + 1);
			box = map->map2d[(int)(rays->x - rays->a)][(int)(rays->y - rays->b
					- 1)];
		}
		if (box == '1')
			break ;
		rays->b++;
	}
}

void	horizontal_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	char	box;

	rays->a = 0.5;
	if (fabs(angle) < EPSILON || fabs(angle - M_PI_2) < EPSILON || fabs(angle
			- M_PI) < EPSILON || fabs(angle - (3 * M_PI_2)) < EPSILON)
	{
		rays->horizontal_distance =rays->horizontal_distance ;
		return ;
	}
	// printf("ENTERING: horizontal check\n");
	while (1)
	{
		rays->horizontal_distance = rays->a / sin(angle);
		rays->b = cos(angle) * rays->horizontal_distance;
		// printf("H--- checking A: %f, B: %f, C: %f\n", rays->a, rays->b,
		//	rays->horizontal_distance);
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a - 1) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
				return ;
			rays->wall_direction = 'S';
			/*printf("1H checking the fields: %d y: %d\n", (int)(rays->x
					- rays->a), (int)(rays->y + rays->b + 1));
			printf("rays->x: %f, rays->y: %f\n", rays->x, rays->y);*/
			box = map->map2d[(int)(rays->x - rays->a - 1)][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 2)
		{
			if ((int)(rays->x + rays->a) >= map->map_height || (int)(rays->y
					+ rays->b) > map->map_width)
			{
				return ;
			}
			rays->wall_direction = 'N';
			// printf("2Horizontal values check ++ : x:%d y: %d\n",
			//((int)(rays->x
			//+ rays->a + 0.5)), (int)(rays->y + rays->b));
			// printf("original X: %d, Y: %d\n", rays->x, rays->y);
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y
					+ rays->b)];
		}
		else if (quarter == 3)
		{
			if ((int)(rays->x + rays->a) > map->map_height || (int)(rays->y
					- rays->b < 0))
				return ;
			rays->wall_direction = 'N';
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y
					- rays->b)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a - 1) < 0 || (int)(rays->y
					- rays->b) > map->map_width)
				return ;
			rays->wall_direction = 'S';
			/*printf("--horizontal-------------im checking the field: x: %d y:
				%d\n", (int)(rays->x - rays->a - 1), (int)(rays->y
					- rays->b));*/
			box = map->map2d[(int)(rays->x - rays->a - 1)][(int)(rays->y
					- rays->b)];
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
