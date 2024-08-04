#include "cub3d.h"

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
    {

        printf("check this player: %f\n", cub->player->player_y);
        if(cub->map->map2d[(int)(cub->player->player_y - 1)][(int)cub->player->player_x] == '0')
        cub->player->player_y -= 1;

    }
		
	if (keycode == KEY_A)
    {
     
        if(cub->map->map2d[(int)(cub->player->player_y)][(int)(cub->player->player_x - 1)] == '0')
        cub->player->player_x -= 1;
 
    }
		
	if (keycode == KEY_S)
    {
   
        if(cub->map->map2d[(int)(cub->player->player_y + 1)][(int)cub->player->player_x] == '0')
       cub->player->player_y += 1;
   
    }
		
	if (keycode == KEY_D)
    {


        if(cub->map->map2d[(int)cub->player->player_y][(int)(cub->player->player_x + 1)] == '0')
        cub->player->player_x += 1;
   
    }
    if(keycode == KEY_LEFT)
    {
        printf("keycode is left, we are adjusting the angle\n");
        cub->player->facing -= FOV/SCREEN_W * 100;

    }
    if(keycode == KEY_RIGHT)
    {
        printf("keycode is left, we are adjustng the angle\n");
        cub->player->facing += FOV/SCREEN_W * 100;

    }
		printf("check KEYS are pressed\n");
	if (keycode == 53)
		end_game(cub);
    printf("before clearing the window\n");
	//mlx_clear_window(&cub->mlx->mlx_ptr, &cub->mlx->win_ptr);
    //mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr
    printf("before render\n");
	render(cub);
	return (0);
}

