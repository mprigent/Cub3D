/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:00:22 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 00:25:07 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_initial_side_dist(t_game *game, t_raycasting ray)
{
	if (ray.rayDirX < 0)
	{
		ray.stepX = -1;
		ray.sideDistX = (game->player_x - ray.mapX) * ray.deltaDistX;
	}
	else
	{
		ray.stepX = 1;
		ray.sideDistX = (ray.mapX + 1.0 - game->player_x) * ray.deltaDistX;
	}
	if (ray.rayDirY < 0)
	{
		ray.stepY = -1;
		ray.sideDistY = (game->player_y - ray.mapY) * ray.deltaDistY;
	}
	else
	{
		ray.stepY = 1;
		ray.sideDistY = (ray.mapY + 1.0 - game->player_y) * ray.deltaDistY;
	}
}

void	perform_dda(t_game *game, t_raycasting ray)
{
	while (ray.hit == 0)
	{
		if (ray.sideDistX < ray.sideDistY)
		{
			ray.sideDistX += ray.deltaDistX;
			ray.mapX += ray.stepX;
			ray.side = 0;
		}
		else
		{
			ray.sideDistY += ray.deltaDistY;
			ray.mapY += ray.stepY;
			ray.side = 1;
		}
		if (ft_iswall(game, ray.mapX, ray.mapY))
				ray.hit = 1;
	}
	if (ray.side == 0)
		ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
	else
		ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);
	ray.lineHeight = (int) (SCREEN_HEIGHT / ray.perpWallDist);
}

void	calculate_texture_coordinate(t_game *game, t_raycasting ray)
{
	ray.drawStart = -ray.lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (ray.drawStart < 0)
		ray.drawStart = 0;
	ray.drawEnd = ray.lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (ray.drawEnd >= SCREEN_HEIGHT)
		ray.drawEnd = SCREEN_HEIGHT - 1;
	if (ray.side == 0)
		ray.wallX = game->player_y + ray.perpWallDist * ray.rayDirY;
	else
		ray.wallX = game->player_x + ray.perpWallDist * ray.rayDirX;
	ray.wallX -= floor(ray.wallX);
	ray.tex = get_texture(game, get_direction(ray.side, ray.side == 0 ? ray.stepX : ray.stepY));
	ray.texX = (int) (ray.wallX * (double) ray.tex->width);
	if (ray.side == 0 && ray.rayDirX > 0)
		ray.texX = ray.tex->width - ray.texX - 1;
	if (ray.side == 1 && ray.rayDirY < 0)
		ray.texX = ray.tex->width - ray.texX - 1;
	ray.step = 1.0 * ray.tex->height / ray.lineHeight;
	ray.texPos = (ray.drawStart - SCREEN_HEIGHT / 2 + ray.lineHeight / 2) * ray.step;
}

void	draw_3d_view(t_game *game, t_raycasting ray, int rayon_x)
{
	for(int y = ray.drawStart; y < ray.drawEnd; y++)
	{
		int texY = ray.texPos;
		ray.texPos += ray.step;
		int color = ft_pixel_color(ray.tex->data, ray.texX, texY);
		ft_pixel(game->img, rayon_x, y, color);
	}
	for (int i = 0; i < ray.drawStart; i++)
		ft_pixel(game->img, rayon_x, i, game->ceil);
	for (int i = ray.drawEnd; i < ray.drawEnd + SCREEN_HEIGHT; i++)
		ft_pixel(game->img, rayon_x, i, game->floor);
}

void	draw_rays_3d(t_game *game, t_raycasting ray)
{
	for (int rayon_x = 0; rayon_x < SCREEN_WIDTH; rayon_x++)
	{
		ray.cameraX = 2 * rayon_x / (double) SCREEN_WIDTH - 1;
		ray.rayDirX = game->dir_x + game->plane_x * ray.cameraX;
		ray.rayDirY = game->dir_y + game->plane_y * ray.cameraX;
		ray.mapX = (int) game->player_x;
		ray.mapY = (int) game->player_y;
		ray.deltaDistX = (ray.rayDirX == 0) ? 1e30 : fabs(1 / ray.rayDirX);
		ray.deltaDistY = (ray.rayDirY == 0) ? 1e30 : fabs(1 / ray.rayDirY);
		ray.hit = 0;
		calculate_initial_side_dist(game, ray);
		perform_dda(game, ray);
		calculate_texture_coordinates(game, ray);
		draw_3d_view(game, ray, rayon_x);
	}
}