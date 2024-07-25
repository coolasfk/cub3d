#include "cub3d.h"

int	render(t_cub *cub)
{
	t_rays	*rays;
	int		i;
	float	angle;

	rays = allocate_memory(0, RAYS, &cub->type);
	i = 0;
	// render_floor();
	// render_ceiling();
	angle = cub->player->facing - PI / 4;
	printf("angle1: %f\n", (angle * 180.0 / PI));
	if (angle < 0)
		angle = 2 * PI - angle*-1;
	printf("angle2: %f\n\n\n", (angle * 180.0 / PI));
	while (i <= SCREEN_W)
	{
		printf("angle3: %f\n", (angle * 180.0 / PI));
		launch_rays(cub->player, cub->map, rays, angle);
		printf("distance to the wall south: %f\n\n\n", rays->distance_to_wall);
		angle = angle + PI / 8;
		if (angle >= 2 * PI)
			angle = 0;
		i += 256;
	}
	return (0);
}

void	launch_rays(t_player *player, t_map *map, t_rays *rays, float angle)
{
	if (angle >= PI + (3 * PI / 4) || angle < (3 * PI / 4))
	{
		printf("facig east\n");
		player_facing_east(player, map, rays, angle);
	}
	else if (angle >= PI / 4 && angle < (3 * PI / 4))
	{
		printf("facig south\n");
		player_facing_south(player, map, rays, angle);
	}
	else if ((angle >= (3 * PI / 4)) && (angle < PI + (PI / 4)))
	{
		printf("facig west\n");
		player_facing_west(player, map, rays, angle);
	}
	else if ((angle >= PI + (PI / 4)) && angle < PI + (3 * PI / 4))
	{
		printf("facig north\n");
		player_facing_north(player, map, rays, angle);
	}
}

void	player_facing_east(t_player *player, t_map *map, t_rays *rays,
		float angle)
{
	
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	while (map->map2d[rays->x][rays->y] != '1'
		&& rays->y < (int)ft_strlen(*map->map2d))
		rays->y++;
        if (angle == 0)
	{
		rays->distance_to_wall = rays->y + 0.5 - 1;
		return ;
	}
	if (angle >= PI + (3 * PI / 4))
	{
		rays->angle_left = 2 * PI - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	if (angle < (PI / 4))
	{
		rays->angle_left = PI / 4 - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	rays->h = rays->y + 0.5 - 1;
	rays->a = tan(rays->angle_left) * rays->h;
	rays->distance_to_wall = sqrt(rays->a * rays->a + rays->h * rays->h);
}

void	player_facing_west(t_player *player, t_map *map, t_rays *rays,
		float angle)
{
	if (angle == PI)
	{
		rays->distance_to_wall = angle;
		return ;
	}
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	while (map->map2d[rays->x][rays->y] != '1' && rays->y > -1)
		rays->y--;
	if (angle >= 3 * PI / 4 && angle < PI)
	{
		rays->angle_left = PI - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	else
	{
		rays->angle_right = angle - PI;
		rays->angle_left = PI / 2 - rays->angle_right;
	}
	rays->h = rays->y + 0.5;
	rays->a = tan(rays->angle_left) * rays->h;
	rays->distance_to_wall = sqrt(rays->a * rays->a + rays->h * rays->h);
}

void	player_facing_north(t_player *player, t_map *map, t_rays *rays,
		float angle)
{
	if (angle == PI + PI / 2)
	{
		rays->distance_to_wall = angle;
		return ;
	}
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	while (map->map2d[rays->x][rays->y] != '1' && rays->x > -1)
		rays->x++;
	if (angle >= PI + (PI / 4) && angle < PI + (3 * PI / 4))
	{
		rays->angle_left = PI + PI / 2 - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	else
	{
		rays->angle_right = angle - PI;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	rays->h = rays->x + 0.5 - 1;
	rays->a = tan(rays->angle_left) * rays->h;
	rays->distance_to_wall = sqrt(rays->a * rays->a + rays->h * rays->h);
}

void	player_facing_south(t_player *player, t_map *map, t_rays *rays,
		float angle)
{
	if (angle == PI / 2)
	{
		rays->distance_to_wall = angle;
		return ;
	}
	rays->x = player->player_x - 0.5;
	rays->y = player->player_y - 0.5;
	while (map->map2d[rays->x] != NULL && map->map2d[rays->x][rays->y] != '1')
		rays->x--;
	if (angle >= PI / 4 && angle < PI / 2)
	{
		rays->angle_left = PI / 2 - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	if (angle <= (3 * PI / 4))
	{
		rays->angle_left = PI / 4 - angle;
		rays->angle_right = PI / 2 - rays->angle_left;
	}
	rays->h = rays->x + 0.5 - 1;
	rays->a = tan(rays->angle_left) * rays->h;
	rays->distance_to_wall = sqrt(rays->a * rays->a + rays->h * rays->h);
}