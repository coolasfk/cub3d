#include "cub3d.h"

void	print_and_exit_specs(char *str, t_specs *specs)
{
	t_cub	*cub;

	cub = get_cub();
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
	free(cub);
	exit(1);
}

void	print_and_exit_map(char *str, t_map *map, char **line)
{
	t_specs	*specs;
	int		i;

	i = 0;
	specs = get_specs();
	if (map != NULL && map->map2d != NULL)
	{
		while (map->map2d[i] != NULL)
		{
			free(map->map2d[i]);
			map->map2d[i] = NULL; 
			i++;
		}
		free(map->map2d);
		map->map2d = NULL; 
	}
	if (line != NULL)
		free(*line); 
	free(map); 
	print_and_exit_specs(str, specs);
}
