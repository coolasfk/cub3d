/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:29:56 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 20:30:43 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extra_check(t_rays *rays, t_map *map)
{
	if (map->map2d[(int)(rays->y + rays->a)][(int)(rays->hit_h)] != '0')
	{
		rays->box = '1';
		return (1);
	}
	return (0);
}

void	check_box_h(t_rays *rays, t_map *map, int quarter)
{
	if (quarter == 1)
	{
		rays->hit_h = rays->x + rays->b;
		rays->box = map->map2d[(int)(rays->y - rays->a
				- 1)][(int)(rays->hit_h)];
	}
	else if (quarter == 2)
	{
		rays->hit_h = rays->x + rays->b;
		rays->box = map->map2d[(int)(rays->y + rays->a)][(int)(rays->hit_h)];
	}
	else if (quarter == 3)
	{
		rays->hit_h = rays->x - rays->b;
		if (extra_check(rays, map))
			return ;
		rays->box = map->map2d[(int)(rays->y + rays->a)][(int)(rays->hit_h)];
	}
	else if (quarter == 4)
	{
		rays->hit_h = rays->x - rays->b;
		rays->box = map->map2d[(int)(rays->y - rays->a
				- 1)][(int)(rays->hit_h)];
	}
}

void	horizontal_angle(t_map *map, t_rays *rays, float angle, int quarter)
{
	if (quarter == 1 || quarter == 4)
		rays->wall_direction_h = 'N';
	else
		rays->wall_direction_h = 'S';
	rays->a = -0.5;
	if (fabs(angle) < EPSILON || fabs(angle - M_PI_2) < EPSILON || fabs(angle
			- M_PI) < EPSILON || fabs(angle - (3 * M_PI_2)) < EPSILON)
		return ;
	while (++rays->a > 0)
	{
		rays->horizontal_distance = rays->a / sin(angle);
		rays->b = cos(angle) * rays->horizontal_distance;
		if ((quarter == 1 && ((int)(rays->y - rays->a - 1) < 0 || (int)(rays->x
				+ rays->b) > map->map_width)) || (quarter == 2
				&& ((int)(rays->y + rays->a) >= map->map_height || (int)(rays->x
						+ rays->b) > map->map_width)) || (quarter == 3
				&& ((int)(rays->y + rays->a) > map->map_height || (int)(rays->x
						- rays->b) < 0)) || (quarter == 4 && ((int)(rays->y
						- rays->a - 1) < 0 || (int)(rays->x
						- rays->b) > map->map_width)))
			return ;
		check_box_h(rays, map, quarter);
		if (rays->box == '1')
			break ;
	}
}
