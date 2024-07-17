#include "cub3d.h"

void	print_and_exit_specs(char *str, t_specs *specs)
{
	printf("%s\n", str);
	if (specs->n_spec != NULL)
		free(specs->n_spec);
	if (specs->s_spec != NULL)
		free(specs->s_spec);
	if (specs->w_spec != NULL)
		free(specs->w_spec);
	if (specs->e_spec != NULL)
		free(specs->e_spec);
	if (specs->ceil_spec != NULL)
		free(specs->ceil_spec);
	if (specs->floor_spec != NULL)
		free(specs->floor_spec);
	if (specs->floor != NULL)
		free(specs->floor);
	if (specs->ceil != NULL)
		free(specs->ceil);
	free(specs);

	exit(1);
}