/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pixel_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:57:53 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 20:54:55 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_rect(t_data *data, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			ft_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_square(t_data *data, int x, int y, int x2, int y2, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x2)
	{
		j = y;
		while (j < y2)
		{
			ft_pixel(data, i, j, color);
			j++;
		}
		i++;
	}
}
