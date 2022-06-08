/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 18:52:22 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_camera(t_game *game, double rot)
{
	//both camera direction and camera plane must be rotated
	double oldDirX = game->dir_x;
	game->dir_x = game->dir_x * cos(rot) - game->dir_y * sin(rot);
	game->dir_y = oldDirX * sin(rot) + game->dir_y * cos(rot);
	double oldPlaneX = game->plane_x;
	game->plane_x = game->plane_x * cos(rot) - game->plane_y * sin(rot);
	game->plane_y = oldPlaneX * sin(rot) + game->plane_y * cos(rot);
}

double	rotate_camera_relative(char c)
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
