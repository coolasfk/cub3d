/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:31:08 by bcai              #+#    #+#             */
/*   Updated: 2024/07/17 19:24:52 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

long	ft_atoi(const char *str)
{
	int		indicator;
	long	result;

	indicator = 1;
	result = 0;
	if(str[0] == '\0')
	return 666;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			indicator *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48) * indicator;
		str++;
	}
	return (result);
}
/*
int	main(int argc, char *argv[])
{
	(void)argc;

	printf("my function %d\n", ft_atoi(argv[1]));
	printf("official atoi %d\n", atoi(argv[1]));
	return (0);
}*/
