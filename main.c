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
	mlx->img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length,
			&mlx->endian);
	mlx_key_hook(cub->mlx->win_ptr, key_hook, &cub);
	mlx_hook(cub->mlx->win_ptr, 17, 0, end_game, &cub);
	render(cub);
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

int	key_hook(int keycode, t_cub *cub)
{
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
}

/*
nt	launch_game(void)
{
	void	*img;
	char	*address;

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
