/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_utils_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:17:24 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 16:24:26 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*get_texture(t_game *game, int direction)
{
	if (direction == NORTH)
		return (game->north);
	if (direction == SOUTH)
		return (game->south);
	if (direction == EAST)
		return (game->east);
	if (direction == WEST)
		return (game->west);
	return (0);
}

int	get_direction(int side, int step)
{
	if (side == 0)
	{
		if (step > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	if (side == 1)
	{
		if (step > 0)
			return (EAST);
		else
			return (WEST);
	}
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

int	ft_iswall(t_game *game, int x, int y)
{
	return (ft_getcaracter(game, x, y) == '1');
}

int	check_filename(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 4)
		return (0);
	return (filename[i - 1] == 'b' && filename[i - 2] == 'u' \
			&& filename[i - 3] == 'c' && filename[i - 4] == '.');
}
