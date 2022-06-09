/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:03:34 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 02:12:59 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_strs_len(map))
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' '
			&& ft_check_closing(map, j, i) != 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_closing(char **map, int x, int y)
{
	if (y == 0 || y + 1 >= ft_strs_len(map))
		return (0);
	if (x == 0 || x + 1 >= ft_strlen(map[y]))
		return (-1);
	if ((x >= ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
			|| (x >= ft_strlen(map[y - 1])
			|| map[y - 1][x] == ' '))
		return (-2);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (-3);
	return (1);
}

int	ft_check_for_missing(t_game *game)
{
	if (!game->north || !game->south || !game->west || !game->east)
		return (0);
	if (game->ceil < 0 || game->floor < 0)
		return (-1);
	return (1);
}
