#include "cub3d.h"

void	change_rgb_to_hex(int *color, t_rgb *rgb)
{
	t_rgb	*ptr;
	ptr = rgb;

	*color = (ptr->value << 16) | (ptr->next->value << 8) | ptr->next->next->value;
}