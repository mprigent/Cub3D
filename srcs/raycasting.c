/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:00:22 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 17:28:59 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_initial_side_dist(t_game *game, t_raycasting *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player_x) \
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player_y) \
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_raycasting *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_iswall(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
}

void	calculate_texture_coordinates(t_game *game, t_raycasting *ray)
{
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0)
		ray->tex = get_texture(game, get_direction(ray->side, ray->step_x));
	else
		ray->tex = get_texture(game, get_direction(ray->side, ray->step_y));
	ray->tex_x = (int)(ray->wall_x * (double) ray->tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
	ray->step = 1.0 * ray->tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

void	draw_3d_view(t_game *game, t_raycasting *ray, int rayon_x)
{
	int	y;
	int	i;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ft_pixel(game->img, rayon_x, y, ft_pixel_color(ray->tex->data,
				ray->tex_x, ray->tex_pos));
		ray->tex_pos += ray->step;
		y++;
	}
	i = 0;
	while (i < ray->draw_start)
	{
		ft_pixel(game->img, rayon_x, i, game->ceil);
		i++;
	}
	i = ray->draw_end;
	while (i < ray->draw_end + SCREEN_HEIGHT)
	{
		ft_pixel(game->img, rayon_x, i, game->floor);
		i++;
	}
}

void	draw_rays_3d(t_game *game, t_raycasting *ray)
{
	int	rayon_x;

	rayon_x = 0;
	while (rayon_x < SCREEN_WIDTH)
	{
		ray->camera_x = 2 * rayon_x / (double) SCREEN_WIDTH - 1;
		ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
		ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
		ray->map_x = (int) game->player_x;
		ray->map_y = (int) game->player_y;
		if (ray->ray_dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		if (ray->ray_dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		ray->hit = 0;
		calculate_initial_side_dist(game, ray);
		perform_dda(game, ray);
		calculate_texture_coordinates(game, ray);
		draw_3d_view(game, ray, rayon_x);
		rayon_x++;
	}
}
