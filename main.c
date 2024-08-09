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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3D");
	if (mlx->mlx_ptr == NULL || mlx->win_ptr == NULL)
		print_and_exit_map("Error: mlx_init error.", cub->map, NULL);

	mlx->img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->addr[IMG] = mlx_get_data_addr(mlx->img, &mlx->bpp[IMG],
			&mlx->line_length[IMG], &mlx->endian[IMG]);
	mlx->north_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->n_spec,
			&mlx->width[NORTH_TEX], &mlx->height[NORTH_TEX]);
	mlx->addr[NORTH_TEX] = mlx_get_data_addr(mlx->north_tex,
			&mlx->bpp[NORTH_TEX], &mlx->line_length[NORTH_TEX],
			&mlx->endian[NORTH_TEX]);
	mlx->south_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->s_spec,
			&mlx->width[SOUTH_TEX], &mlx->height[SOUTH_TEX]);
	mlx->addr[SOUTH_TEX] = mlx_get_data_addr(mlx->south_tex,
			&mlx->bpp[SOUTH_TEX], &mlx->line_length[SOUTH_TEX],
			&mlx->endian[SOUTH_TEX]);
	mlx->east_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->e_spec,
			&mlx->width[EAST_TEX], &mlx->height[EAST_TEX]);
	mlx->addr[EAST_TEX] = mlx_get_data_addr(mlx->east_tex, &mlx->bpp[EAST_TEX],
			&mlx->line_length[EAST_TEX], &mlx->endian[EAST_TEX]);
	mlx->west_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->w_spec,
			&mlx->width[WEST_TEX], &mlx->height[WEST_TEX]);
	mlx->addr[WEST_TEX] = mlx_get_data_addr(mlx->west_tex, &mlx->bpp[WEST_TEX],
			&mlx->line_length[WEST_TEX], &mlx->endian[WEST_TEX]);
	render(cub);
	mlx_hook(cub->mlx->win_ptr, 17, 0, end_game, cub);
	mlx_key_hook(mlx->win_ptr, key_hook, cub);
	mlx_loop(mlx->mlx_ptr);
	return (mlx);
}

int	end_game(t_cub *cub)
{
	if (cub->mlx->win_ptr)
		mlx_destroy_window(cub->mlx->mlx_ptr, cub->mlx->win_ptr);
	exit(0);
	return (0);
}
