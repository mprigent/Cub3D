/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_utils_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:17:24 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 20:20:33 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*get_texture(t_game *game, int direction)
{
	switch (direction)
	{
		case NORTH: return (game->north);
		case SOUTH: return (game->south);
		case EAST: return (game->east);
		case WEST: return (game->west);
	}
	return (NULL);
}

int	get_direction(int side, int step)
{
	if (side == 0)
		return (step > 0 ? SOUTH : NORTH);
	if (side == 1)
		return (step > 0 ? EAST : WEST);
	return (-1);
}

char	ft_getcaracter(t_game *game, int x, int y)
{
	if (y < 0 || y >= ft_strs_len(game->map))
		return (-1);
	if (x < 0 || x >= ft_strlen(game->map[y]))
		return (-2);
	return (game->map[y][x]);
}

int		ft_iswall(t_game *game, int x, int y)
{
	return (ft_getcaracter(game, x, y) == '1');
}
