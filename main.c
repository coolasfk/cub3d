#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub *cub;
	first_check(argc, argv);
    cub = set_cub();
	set_specs(argv[1]);
	cub->map = set_map(argv[1]);
    printf("im here all good");
}