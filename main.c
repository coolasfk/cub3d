#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub cub;
	first_check(argc, argv);
	set_specs(argv[1]);
    printf("----------------check!!!!\n");
	init(&cub);
	cub.specs = get_specs();
	cub.map = set_map(argv[1]);
}