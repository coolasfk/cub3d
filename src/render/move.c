#include "cub3d.h"

int	key_hook(int keycode, t_cub *cub)
{
	printf("cub->rays->wall_direction check: %c\n", cub->rays->wall_direction);
    printf("checking map position now top check : y: %d, x: %d\n", (int)(cub->player->player_y), (int)(cub->player->player_x));
	if (keycode == KEY_W)
	{
		printf("W check this player: %f\n", cub->player->player_y);
		if (cub->player->facing >= PI + PI/4 && cub->player->facing < PI + 3 * PI/4)
		{
            //NORTH
			if (cub->map->map2d[(int)(cub->player->player_x-1
				)][(int)cub->player->player_y] == '0')
				cub->player->player_x -= 1;
		}
		else if (cub->player->facing >= PI + 3 * PI/4 || cub->player->facing < PI/4)
		{
            //EAST
            printf("payer facing EAST , W key is pressed\n");
			if (cub->map->map2d[(int)cub->player->player_x][(int)(cub->player->player_y+1)] == '0')
				cub->player->player_y += 1;
		}
		else if (cub->player->facing >= PI/4 && cub->player->facing < 3 * PI/4)
		{
            //SOUTH
             printf("payer facing SOUTH, W key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x
					+ 1)][(int)cub->player->player_y] == '0')
				cub->player->player_x += 1;
		}
		else if (cub->player->facing >= 3 * PI/4 && cub->player->facing < PI + PI/4)
		{
            //WEST
             printf("payer facing WEST , W key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x)][(int)(cub->player->player_y-1)] == '0')
				cub->player->player_y -= 1;
		}
	}
	if (keycode == KEY_A)
	{
		if (cub->player->facing >= PI + PI/4 && cub->player->facing < PI + 3 * PI/4)
		{
            //NORTH
             printf("payer facing NORTH , A key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x)][(int)cub->player->player_y-1] == '0')
				cub->player->player_y -= 1;
		}
		else if (cub->player->facing >= PI + 3 * PI/4 || cub->player->facing < PI/4)
		{
            //EAST
             printf("payer facing EAST , A key is pressed\n");
			if (cub->map->map2d[(int)cub->player->player_x -1][(int)(cub->player->player_y)] == '0')
				cub->player->player_x -= 1;
		}
		else if (cub->player->facing >= PI/4 && cub->player->facing < 3 * PI/4)
		{
            //SOUTH
             printf("payer facing SOUTH , A key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x
				)][(int)cub->player->player_y+1] == '0')
				cub->player->player_y += 1;
		}
		else if (cub->player->facing >= 3 * PI/4 && cub->player->facing < PI + PI/4)
		{
            //WEST
            printf("payer facing WEST , A key is pressed\n");
            printf("checking map position now : y: %d, x: %d\n", (int)(cub->player->player_y), (int)(cub->player->player_x));
			if (cub->map->map2d[(int)(cub->player->player_x +1)][(int)(cub->player->player_y
					)] == '0')
				cub->player->player_x += 1;
		}
	
	}
	if (keycode == KEY_S)
	{
		if (cub->player->facing >= PI + PI/4 && cub->player->facing < PI + 3 * PI/4)
		{
            //NORTH
             printf("player facing north, s key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x+1)][(int)cub->player->player_y] == '0')
				cub->player->player_x+= 1;
		}
		else if (cub->player->facing >= PI + 3 * PI/4 || cub->player->facing < PI/4)
		{
            //EAST
             printf("player facing east, s key is pressed\n");
			if (cub->map->map2d[(int)cub->player->player_x][(int)(cub->player->player_y
					- 1)] == '0')
				cub->player->player_y -= 1;
		}
		else if (cub->player->facing >= PI/4 && cub->player->facing < 3 * PI/4)
		{
            //SOUTH
            printf("player facing south, s key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x-1)][(int)cub->player->player_y] == '0')
				cub->player->player_x -= 1;
		}
		else if (cub->player->facing >= 3 * PI/4 && cub->player->facing < PI + PI/4)
		{
            //WEST
			if (cub->map->map2d[(int)(cub->player->player_x)][(int)(cub->player->player_y +1)] == '0')
				cub->player->player_y += 1;
		}
	
	}
	if (keycode == KEY_D)
	{
		if (cub->player->facing >= PI + PI/4 && cub->player->facing < PI + 3 * PI/4)
		{
            //NORTH
              printf("payer facing NORTH , D key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x)][(int)cub->player->player_y+1] == '0')
				cub->player->player_y += 1;
		}
		else if (cub->player->facing >= PI + 3 * PI/4 || cub->player->facing < PI/4)
		{
            //EAST
             printf("payer facing EAST , D key is pressed\n");
			if (cub->map->map2d[(int)cub->player->player_x +1][(int)(cub->player->player_y
					)] == '0')
				cub->player->player_x += 1;
		}
		else if (cub->player->facing >= PI/4 && cub->player->facing < 3 * PI/4)
		{
            //SOUTH
            printf("payer facing SOUTH , D key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x
					+ 1)][(int)cub->player->player_y-1] == '0')
				cub->player->player_y -= 1;
		}
		else if (cub->player->facing >= 3 * PI/4 && cub->player->facing < PI + PI/4)
		{
            //WEST
            printf("payer facing WEST , D key is pressed\n");
			if (cub->map->map2d[(int)(cub->player->player_x-1)][(int)(cub->player->player_y -1
					)] == '0')
				cub->player->player_x -= 1;
		}
	
	}
	if (keycode == KEY_LEFT)
	{
		printf("keycode is left, we are adjusting the angle\n");
		cub->player->facing -= FOV / SCREEN_W * 100;
	}
	if (keycode == KEY_RIGHT)
	{
		printf("keycode is left, we are adjustng the angle\n");
		cub->player->facing += FOV / SCREEN_W * 100;
	}
	if (keycode == 53)
		end_game(cub);
	// mlx_clear_window(&cub->mlx->mlx_ptr, &cub->mlx->win_ptr);
	// mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr
	printf("checking player position before render : y: %d, x: %d\n", (int)(cub->player->player_y), (int)(cub->player->player_x));
	render(cub);
	return (0);
}
