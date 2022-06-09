/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:18:23 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 14:28:06 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_init(char **argv, t_game *game)
{
	if (!game)
	{
		ft_error("Game allocation error\n");
		return (0);
	}
	if (ft_init_mlx(game) != 1)
	{
		ft_error("Mlx initialisation error\n");
		ft_free_game(game);
		return (-1);
	}
	if (ft_init_global(game, argv[1]) != 1)
	{
		ft_free_game(game);
		return (-2);
	}
	return (1);
}

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (0);
	game->floor = -1;
	game->ceil = -1;
	game->dir_x = -1;
	game->plane_y = 0.66;
	return (game);
}
