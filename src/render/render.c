#include "cub3d.h"

int	render(t_cub *cub)
{
	t_rays	*rays;
	float	angle;
	int		i;

	i = 0;
	rays = allocate_memory(0, RAYS, &cub->type);
	// angle = cub->player->facing + PI;
	angle = PI + PI/57;
	while (i < SCREEN_W)
	{
		if (angle < 0)
			angle += 2 * PI;
		if (angle >= 2 * PI)
			angle -= 2 * PI;
		// printf("------angle render  check %f\n", angle * 180 / PI);
		launch_rays(cub->player, cub->map, rays, angle);
		// printf("comparing: horizontal: %f, vertical: %f\n",
			//rays->horizontal_distance, rays->vertical_distance);
			if (rays->horizontal_distance > rays->vertical_distance)
				rays->distance_to_wall = rays->vertical_distance;
			else
				rays->distance_to_wall = rays->horizontal_distance;
			// rays->distance_to_wall *= cos(angle);
			fix_fisheye(&rays->distance_to_wall, i);
			render_walls(cub->mlx, rays, i);
			// angle += 2 * PI / 180;
			// angle += FOV / SCREEN_W * 4;
			angle += FOV / SCREEN_W;
			// printf("wall distance %f\n\n\n", rays->distance_to_wall);
			// i += 30;
			// i += 4;
			i++;
	}
	free(rays);
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
	// print2d_array(map->map2d);
	rays->x = player->player_x;
	rays->y = player->player_y;
	if (angle >= PI + (PI / 2))
	{
		angle = 2 * PI - angle;
		// printf("first quarter\n");
		// printf("angle1: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 1);
		horizontal_angle(map, rays, angle, 1);
		// rays->distance_to_wall = cos(angle);
	}
	else if (angle < PI / 2)
	{
		// printf("--------------------------------------------------second quarter\n");
		// printf("angle2: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 2);
		horizontal_angle(map, rays, angle, 2);
		// rays->distance_to_wall = cos(angle);
	}
	else if (angle >= (PI / 2) && angle < PI)
	{
		angle = PI - angle;
		//printf("angle3: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 3);
		horizontal_angle(map, rays, angle, 3);
	}
	else if (angle >= PI && angle < PI + PI / 2)
	{
		angle = angle - PI;
		//printf("angle4: %f\n", (angle * 180.0 / PI));
		vertical_angle(map, rays, angle, 4);
		horizontal_angle(map, rays, angle, 4);
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
		/*printf("Vertical: /\\- A: %f, B: %f, C: %f\n", rays->a, rays->b,
			rays->vertical_distance);*/
		// printf("2V values check: %d y: %d\n", (int)(rays->x + rays->b),
		//(int)(rays->y + rays->a));
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
				return ;
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
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y - rays->b
					- 1)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a) < 0 || (int)(rays->y - rays->b
					- 1) < 0)
				return ;
			/*printf("-vetical--------------im checking the field: x: %d y:
				%d\n",
				(int)(rays->x - rays->a), (int)(rays->y - rays->b - 1) + 1);*/
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
		/*printf("H--- checking A: %f, B: %f, C: %f\n", rays->a, rays->b,
			rays->horizontal_distance);*/
		if (quarter == 1)
		{
			if ((int)(rays->x - rays->a - 1) < 0 || (int)(rays->y
					+ rays->b) > map->map_width)
				return ;
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
			box = map->map2d[(int)(rays->x + rays->a)][(int)(rays->y
					- rays->b)];
		}
		else if (quarter == 4)
		{
			if ((int)(rays->x - rays->a - 1) < 0 || (int)(rays->y
					- rays->b) > map->map_width)
				return ;
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
