/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:11 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 20:19:49 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free_rgb(specs);
	free(specs);
	free(cub->mlx);
	free(cub->rays);
	free(cub);
	exit(1);
}

void	free_rgb(t_specs *specs)
{
	t_rgb	*ptr;

	while (specs->floor != NULL)
	{
		ptr = specs->floor;
		specs->floor = specs->floor->next;
		free(ptr);
	}
	while (specs->ceil != NULL)
	{
		ptr = specs->ceil;
		specs->ceil = specs->ceil->next;
		free(ptr);
	}
}
/*
void	free_mlx_rgb(void)
{
	t_cub	*cub;

	cub = get_cub();
	free(cub->player);
	free(cub->rays);
}*/

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
			free(map->check[i]);
			free(map->map2d[i]);
			map->map2d[i] = NULL;
			map->check[i] = NULL;
			i++;
		}
		free(map->check);
		free(map->map2d);
		map->map2d = NULL;
		map->check = NULL;
		free(map);
	}
	if (line != NULL)
		free(*line);
	print_and_exit_specs(str, specs);
}
