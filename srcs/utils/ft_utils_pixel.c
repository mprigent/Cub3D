/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 21:05:45 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_pixel_color(void *image, int x, int y)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*addr;
	char	*dst;

	addr = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	dst = addr + ((y * line_bytes) + x * (pixel_bits / 8));
	return (*(unsigned int *)dst);
}

int	ft_rgb_to_int(int r, int g, int b)
{
	return (65536 * r + 256 * g + b);
}
