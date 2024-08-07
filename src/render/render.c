#include "cub3d.h"

int	render(t_cub *cub)
{
	float	angle;
	int		i;

	i = 0;
	angle = cub->player->facing;
	angle -= PI / 4;
	if (angle < 0)
		cub->player->facing += 2 * PI;
	if (angle >= 2 * PI)
		cub->player->facing -= 2 * PI;
	printf("check cub->player->facing %f\n", angle * 180 / PI);
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
		{
			cub->rays->distance_to_wall = cub->rays->vertical_distance;
			cub->rays->wall_direction = cub->rays->wall_direction_v;
			cub->rays->wall_hit = cub->rays->wall_hit_v;
			// printf("vertical\n");
		}
		else
		{
			cub->rays->distance_to_wall = cub->rays->horizontal_distance;
			cub->rays->wall_direction = cub->rays->wall_direction_h;
			cub->rays->wall_hit = cub->rays->wall_hit_h;
			// printf("horizontal\n");
		}
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
	dst = mlx->addr[4] + (y * mlx->line_length[4] + x * (mlx->bpp[4] / 8));
	*(unsigned int *)dst = color;
}

void	render_walls(t_mlx *mlx, t_rays *rays, int x, t_specs *specs)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		y;
	char	*pixel;
	int		tex_x;
	float	tex_y;
	int		texture_height;
	int		d;

	wall_height = (int)(PLANE / rays->distance_to_wall * 1.6);
	draw_start = -wall_height / 2 + SCREEN_H / 2;
	draw_end = wall_height / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	if (rays->wall_direction == 'N')
	{
		mlx->texture = NORTH_TEX;
	}
	else if (rays->wall_direction == 'S')
	{
		mlx->texture = SOUTH_TEX;
		tex_x = mlx->width[mlx->texture] - ((int)((rays->wall_hit - floor(rays->wall_hit))
				* mlx->width[mlx->texture]));
	}
	else if (rays->wall_direction == 'E')
	{
		mlx->texture = EAST_TEX;
	}
	else if (rays->wall_direction == 'W')
	{
		mlx->texture = WEST_TEX;
	}
	tex_x = (int)((rays->wall_hit - floor(rays->wall_hit))
			* mlx->width[mlx->texture]);
	

	
	
	texture_height = mlx->height[mlx->texture];
	tex_y = 0;
	// printf("line 115 render walls \n");
	y = draw_start;
	while (y < draw_end)
	{
		d = (y - SCREEN_H / 2 + wall_height / 2) * texture_height;
		// printf("line 120 render walls, d: %d, y: %d, wall_height: %d\n", d,
		// y, wall_height);
		tex_y = d / wall_height;
		// printf("line 122 render walls, tex_y: %f, tex_x: %d \n", tex_y,
		// tex_x);
		pixel = mlx->addr[mlx->texture]
			+ ((int)(tex_y)*mlx->line_length[mlx->texture] + tex_x
				* (mlx->bpp[mlx->texture] / 8));
		// printf("line 126 render walls, check pixel: %d \n", *(int *)pixel);
		my_mlx_pixel_put(mlx, x, y, *(unsigned int *)pixel);
		// printf("line 128 render walls \n");
		y++;
	}
	// printf("line 126 render walls \n");
	y = draw_end;
	while (y < SCREEN_H)
	{
		my_mlx_pixel_put(mlx, x, y, specs->floor_color);
		y++;
	}
	y = 0;
	// printf("line 134 render walls \n");
	while (y < draw_start)
	{
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
			rays->wall_direction_v = 'E';
			rays->wall_hit_v = rays->x - rays->a;
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
			rays->wall_hit_v = rays->x + rays->a;
			rays->wall_direction_v = 'E';
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
			rays->wall_hit_v = rays->x + rays->a;
			rays->wall_direction_v = 'W';
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y - rays->b
					- 1)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y - rays->b
					- 1) < 0)
				return ;
			rays->wall_hit_v = rays->x - rays->a;
			rays->wall_direction_v = 'W';
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
		rays->horizontal_distance = rays->horizontal_distance;
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
			rays->wall_direction_h = 'N';
			rays->wall_hit_h = rays->y + rays->b;
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
			rays->wall_hit_h = rays->y + rays->b;
			rays->wall_direction_h = 'S';
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
			rays->wall_hit_h = rays->y - rays->b;
			rays->wall_direction_h = 'S';
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y
					- rays->b)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a - 1) < 0 || (int)(rays->y
					- rays->b) > map->map_width)
				return ;
			rays->wall_hit_h = rays->y - rays->b;
			rays->wall_direction_h = 'N';
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
