/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:22:13 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 01:23:25 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_for_missing(t_game *game)
{
	if (!game->north || !game->south || !game->west || !game->east)
		return (0);
	if (game->ceil < 0 || game->floor < 0)
		return (-1);
	return (1);
}

int	ft_read_parameters(t_game *game, char *config)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (config[i])
	{
		if (config[i] == '\n')
		{
			if (ft_read_parameter(game, config, i - len, len) != 1)
				return (0);
			len = 0;
		}
		else
			len++;
		i++;
	}
	if (ft_check_for_missing(game) != 1)
		return (-1);
	return (1);
}
