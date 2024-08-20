/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:30 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/08/20 15:24:50 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_rgb_to_hex(int *color, t_rgb *rgb)
{
	t_rgb	*ptr;

	ptr = rgb;
	*color = (ptr->value << 16) | (ptr->next->value << 8)
		| ptr->next->next->value;
}
