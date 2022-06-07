/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:55:21 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/07 15:06:57 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_readint(char *str, int from, int end)
{
	int i = from;
	int result = 0;
	
	if (from > end)
		return (-1);
	while (i <= end)
	{
		if (!is_numeric(str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int ft_rgb_write(char *str, int *rgb)
{
	int start;
	int count;
	int	i;
	
	i = 0;
	start = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			rgb[count] = ft_readint(str, start, i - 1);
			count++;
			start = i + 1;
		}
		if (i + 1 == ft_strlen(str))
		{
			rgb[count] = ft_readint(str, start, ft_strlen(str) - 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int check_value(int i)
{
	return (i >= 0 && i <= 255);
}

int	check_format(char *str)
{
	int comma;
	int i;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma++;
		i++;
	}
	if (comma == 2 && ft_strlen(str) >= 5)
		return (1);
	return (0);
}

int ft_rgb(char *str)
{
	int ret;
	int *rgb;
	
	if (check_format(str) != 1)
		return (-1);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (-2);
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	ft_rgb_write(str, rgb);
	if (!check_value(rgb[0]) || !check_value(rgb[1]) || !check_value(rgb[2]))
	{
		free(rgb);
		return (-3);
	}
	ret = RGBtoInt(rgb[0], rgb[1], rgb[2]);
	printf("Color is 0x%d (%d %d %d)\n", ret, rgb[0], rgb[1], rgb[2]);
	ret = 0;
	free(rgb);
	return (ret);
}