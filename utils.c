/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/07 13:47:42 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
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

float	ft_dist(float ax, float ay, float bx, float by, float ang)
{
	(void) ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float degToRad(float a)
{
	return a*M_PI/180.0;
}

float FixAng(float a)
{
	if (a > 359) { a -= 360;}
	if (a < 0) { a += 360;} 
	return a;
}

float distance(float ax, float ay, float bx, float by, float ang)
{
	return cos(degToRad(ang))*(bx-ax) - sin(degToRad(ang))*(by-ay);
}

int RGBtoInt(int r, int g, int b)
{
    return (r << 0) | (g << 8) | (b << 16);
}
