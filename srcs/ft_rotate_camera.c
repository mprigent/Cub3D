/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 01:29:22 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_rotate_camera(t_game *game, double rot)
{
	double	old_plane_x;
	double	old_dir_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot) - game->dir_y * sin(rot);
	game->dir_y = old_dir_x * sin(rot) + game->dir_y * cos(rot);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot) - game->plane_y * sin(rot);
	game->plane_y = old_plane_x * sin(rot) + game->plane_y * cos(rot);
}

double	ft_rotate_camera_relative(char c)
{
	if (c == 'N')
		return (NORTH_RADIANS);
	if (c == 'S')
		return (SOUTH_RADIANS);
	if (c == 'W')
		return (WEST_RADIANS);
	if (c == 'E')
		return (EAST_RADIANS);
	return (0);
}
