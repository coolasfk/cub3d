#include "cub3d.h"

int	render(t_cub *cub)
{
	// int	i;
	// i = 0;
	// render_floor();
	// render_ceiling();
	/*
	while (i < 1024)
{
	launch_rays(cub->player);
	i++;
}*/
	launch_rays(cub->player, cub->map);
	return (0);
}

void	launch_rays(t_player *player, t_map *map)
{
	int	i;
	int	j;
	float	a;
	float	b;
	float	c;
	float	angle_left;

	// int	distance_to_wall;
	// int	h;
	float	angle_right;
	// distance_to_wall = 0;
	i = player->player_x - 0.5;
	j = player->player_y - 1.5;
	if (player->facing >= PI + (3 * PI / 4) || player->facing <= (3 * PI / 4))
		;
	{
		while (map->map2d[i][j] != '1' && j < (int)ft_strlen(*map->map2d))
			j++;
		printf("player->facing %f\n", player->facing);
		if (player->facing >= PI + (3 * PI / 4))
		{
			angle_left = 2 * PI - player->facing;
			angle_right = PI / 2 - angle_left;
		}
		if (player->facing <= (3 * PI / 4))
		{
			angle_left = PI / 4 - player->facing;
            angle_right =  PI / 2 - angle_left;
		}
		printf("angle right: %f\n", angle_right);
		printf("checking the angle left: %f\n", angle_left);
		b = j+0.5;
		printf("height: %f\n", b);
		a = tan(angle_left) * b;
		c = sqrt(a * a + b * b);
		printf("distance to the wall: %f\n", c);
	}
	printf("player x: %f\n", player->player_x);
	printf("player y:%f\n", player->player_y);
}
