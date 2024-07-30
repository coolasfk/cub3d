#include "cub3d.h"

/*
void	change_rgb_to_hex(t_specs *specs, t_rgb *rgb, char **hash_line)
{
	t_type	*type;
	char	hash[3] = "0x";
	t_rgb	*ptr;

	(void)specs;
	type = NULL;
	ptr = rgb;
	while (ptr != NULL)
	{
		loop_rbg(ptr->value, hash_line, type);
		ptr = ptr->next;
	}
	(*hash_line) = ft_strjoin(hash, (*hash_line));
	printf("specs floor check %s\n", (*hash_line));
}

void	loop_rbg(char *temp, char **spec, t_type *type)
{
	int		num;
	char	new[4];
	char	hex[17] = "0123456789ABCDEF";
	t_type	*type;
	char	hash[3] = "0x";
	t_rgb	*ptr;
	

	(void)type;
	num = ft_atoi(temp);
	if (num < 16)
	{
		new[0] = '0';
		new[1] = hex[num];
		new[2] = '\0';
	}
	else
	{
		new[0] = hex[num / 16];
		new[1] = hex[num % 16];
		new[2] = '\0';
	}
	(*spec) = ft_strjoin((*spec), new);
}*/
void	change_rgb_to_hex(int *color, t_rgb *rgb)
{
	t_rgb	*ptr;
	ptr = rgb;

	*color = (ptr->value << 16) | (ptr->next->value << 8) | ptr->next->next->value;
}
// 5D3FFE