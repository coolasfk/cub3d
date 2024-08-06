#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	first_check(argc, argv);
	cub = set_cub(argv);
	cub->mlx = init_mlx(cub->mlx, cub);
	printf("check\n");
}

t_mlx	*init_mlx(t_mlx *mlx, t_cub *cub)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
	{
		printf("Error: mlx_init error.\n");
		return (NULL);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3D");
	if (mlx->win_ptr == NULL)
	{
		printf("Error: mlx_init error.\n");
		return (NULL);
	}
	printf("---cub specs check %s\n", cub->specs->s_spec);
	mlx->img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->addr[IMG] = mlx_get_data_addr(mlx->img, &mlx->bpp[IMG],
			&mlx->line_length[IMG], &mlx->endian[IMG]);
	//mlx->north_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->n_spec,
			//&mlx->width, &mlx->height);
				mlx->north_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->n_spec,
			&mlx->width, &mlx->height);
	mlx->addr[NORTH_TEX] = mlx_get_data_addr(mlx->north_tex, &mlx->bpp[NORTH_TEX],
			&mlx->line_length[NORTH_TEX], &mlx->endian[NORTH_TEX]);
	mlx->south_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->s_spec,
			&mlx->width, &mlx->height);
		mlx->addr[SOUTH_TEX] = mlx_get_data_addr(mlx->south_tex, &mlx->bpp[SOUTH_TEX],
			&mlx->line_length[SOUTH_TEX], &mlx->endian[SOUTH_TEX]);
	mlx->east_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->e_spec,
			&mlx->width, &mlx->height);
		mlx->addr[EAST_TEX] = mlx_get_data_addr(mlx->east_tex, &mlx->bpp[EAST_TEX],
			&mlx->line_length[EAST_TEX], &mlx->endian[EAST_TEX]);
	mlx->west_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->w_spec,
			&mlx->width, &mlx->height);
	mlx->addr[WEST_TEX] = mlx_get_data_addr(mlx->west_tex, &mlx->bpp[WEST_TEX],
			&mlx->line_length[WEST_TEX], &mlx->endian[WEST_TEX]);
	render(cub);
	printf("INIT MLX check this player: %f\n", cub->player->player_y);
	mlx_hook(cub->mlx->win_ptr, 17, 0, end_game, cub);
	mlx_key_hook(mlx->win_ptr, key_hook, cub);
	mlx_loop(mlx->mlx_ptr);
	return (mlx);
}

int	end_game(t_cub *cub)
{
	/*
	mlx_destroy_image(v->mx, v->im[0]);*/
	if (cub->mlx->win_ptr)
		mlx_destroy_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr);
	exit(0);
	return (0);
}
/*
int	key_hook(int keycode, t_cub *cub)
{
	void	*img;
	char	*address;

	if (keycode == KEY_W)
		printf("key 13 is pressed\n");
	if (keycode == KEY_A)
		printf("key 13 is pressed\n");
	if (keycode == KEY_S)
		printf("key 13 is pressed\n");
	if (keycode == KEY_D)
		printf("key 13 is pressed\n");
	if (keycode == ESC)
		end_game(cub);
	mlx_clear_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr);
	return (0);
}*/
/*
nt	launch_game(void)
{
	img = mlx_new_image(data()->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data()->img.pointer_to_image = img;
	address = mlx_get_data_address(data()->img.pointer_to_image, \
		&data()->img.bits_per_pixel, &data()->img.line_length, \
		&data()->img.endian);
	data()->img.address = address;
	draw_floor();
	draw_ceiling();
	raycast_loop();
	hooks();
	data()->var.frame_time = 16 / 1000.0;
	data()->var.move_speed = data()->var.frame_time * 5.0;
	data()->var.rotate_speed = data()->var.frame_time * 3.0;
	mlx_put_image_to_window(data()->mlx, data()->win, \
		data()->img.pointer_to_image, 0, 0);
	mlx_destroy_image(data()->mlx, data()->img.pointer_to_image);
	return (0);
}
*/
