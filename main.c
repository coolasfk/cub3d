#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub cub;
	first_check(argc, argv);
	init(&cub);
	set_specs(argv[1]);
	cub.specs = get_specs();
	cub.map = set_map(argv[1]);
}