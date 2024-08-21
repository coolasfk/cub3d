#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	first_check(argc, argv);
	cub = set_cub(argv);
	cub->mlx = init_mlx(cub->mlx, cub);
}

void	first_init(t_mlx *mlx, t_cub *cub)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
	{
		printf("Error: cannot initialize mlx.\n");
		end_game(cub);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3D");
	if (mlx->win_ptr == NULL)
	{
		printf("Error: cannot initialize a window.\n");
		end_game(cub);
	}
	mlx->img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	if (mlx->win_ptr == NULL)
	{
		printf("Error: cannot initialize a main image.\n");
		end_game(cub);
	}
	mlx->addr[IMG] = mlx_get_data_addr(mlx->img, &mlx->bpp[IMG],
			&mlx->line_length[IMG], &mlx->endian[IMG]);
	if (mlx->addr[IMG] == NULL)
	{
		printf("Error: cannot find the address of the image.\n");
		end_game(cub);
	}
}
void	second_init(t_mlx *mlx, t_cub *cub)
{
	mlx->north_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->n_spec,
			&mlx->width[NORTH_TEX], &mlx->height[NORTH_TEX]);
	if (mlx->north_tex == NULL)
	{
		printf("Error: problem reading north_texture.\n");
		end_game(cub);
	}
	mlx->addr[NORTH_TEX] = mlx_get_data_addr(mlx->north_tex,
			&mlx->bpp[NORTH_TEX], &mlx->line_length[NORTH_TEX],
			&mlx->endian[NORTH_TEX]);
	if (mlx->addr[NORTH_TEX] == NULL)
	{
		printf("Error: cannot find the address of the north texture.\n");
		end_game(cub);
	}
	mlx->south_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->s_spec,
			&mlx->width[SOUTH_TEX], &mlx->height[SOUTH_TEX]);
	if (mlx->south_tex == NULL)
	{
		printf("Error: problem reading south_texture.\n");
		end_game(cub);
	}
	mlx->addr[SOUTH_TEX] = mlx_get_data_addr(mlx->south_tex,
			&mlx->bpp[SOUTH_TEX], &mlx->line_length[SOUTH_TEX],
			&mlx->endian[SOUTH_TEX]);
	if (mlx->addr[SOUTH_TEX] == NULL)
	{
		printf("Error: cannot find the address of the north texture.\n");
		end_game(cub);
	}
}
void	third_init(t_mlx *mlx, t_cub *cub)
{
	mlx->east_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->e_spec,
			&mlx->width[EAST_TEX], &mlx->height[EAST_TEX]);
	if (mlx->east_tex == NULL)
	{
		printf("Error: problem reading east_texture.\n");
		end_game(cub);
	}
	mlx->addr[EAST_TEX] = mlx_get_data_addr(mlx->east_tex, &mlx->bpp[EAST_TEX],
			&mlx->line_length[EAST_TEX], &mlx->endian[EAST_TEX]);
	if (mlx->addr[EAST_TEX] == NULL)
	{
		printf("Error: cannot find the address of the east_texture.\n");
		end_game(cub);
	}
	mlx->west_tex = mlx_xpm_file_to_image(mlx->mlx_ptr, cub->specs->w_spec,
			&mlx->width[WEST_TEX], &mlx->height[WEST_TEX]);
	if (mlx->west_tex == NULL)
	{
		printf("Error: problem reading west_texture.\n");
		end_game(cub);
	}
	mlx->addr[WEST_TEX] = mlx_get_data_addr(mlx->west_tex, &mlx->bpp[WEST_TEX],
			&mlx->line_length[WEST_TEX], &mlx->endian[WEST_TEX]);
	if (mlx->addr[EAST_TEX] == NULL)
	{
		printf("Error: cannot find the address of the west_texture.\n");
		end_game(cub);
	}
}

t_mlx	*init_mlx(t_mlx *mlx, t_cub *cub)
{
	first_init(mlx, cub);
	second_init(mlx, cub);
	third_init(mlx, cub);
	render(cub);
	mlx_hook(cub->mlx->win_ptr, 17, 0, end_game, cub);
	mlx_key_hook(mlx->win_ptr, key_hook, cub);
	mlx_loop(mlx->mlx_ptr);
	return (mlx);
}

