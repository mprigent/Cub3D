/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pixel_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:57:53 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 19:58:40 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_rect(t_data *data, int x, int y, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			ft_pixel(data, x + i, y + j, color);	
		}
	}
}

void	ft_square(t_data *data, int x, int y, int x2, int y2, int color)
{
	for (int i = x; i < x2; i++)
	{
		for (int j = y; j < y2; j++)
		{
			ft_pixel(data, i, j, color);
		}
	}
}
