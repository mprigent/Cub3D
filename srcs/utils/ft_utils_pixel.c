/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 19:58:46 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT )
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int		ft_pixel_color(void *image, int x, int y)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	
	char *addr = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	char *dst = addr + ((y * line_bytes) + x * (pixel_bits / 8));
	return (*(unsigned int*)dst);
}

int		ft_pixels(int x, int y, int x2, int y2)
{
	int	delta_x = x2 - x;
	int	delta_y = y2 - y;
	
	return (sqrt((delta_x * delta_x) + (delta_y * delta_y)));
}

void	ft_line(t_data *data, int x, int y, float dx, float dy,
float pixels, int color)
{
	float pixel_x = x;
	float pixel_y = y;
	
	while (pixels-- > 0)
	{
		ft_pixel(data, pixel_x, pixel_y, color);
		pixel_x += dx;
		pixel_y += dy;
	}
}

int ft_rgb_to_int(int r, int g, int b)
{
	return (65536 * r + 256 * g + b);
}
