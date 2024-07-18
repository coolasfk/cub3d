#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub *cub;
	first_check(argc, argv);
    cub = set_cub(argv);
    //init_mlx();

    //render(cub);
    if(cub)
    printf("im here all good");
}