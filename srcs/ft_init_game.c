/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:18:23 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 13:56:00 by mprigent         ###   ########.fr       */
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

	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	game->img = 0;
	game->map = 0;
	game->mlx = 0;
	game->mlx_win = 0;
	game->north = 0;
	game->south = 0;
	game->east = 0;
	game->west = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_w = 0;
	game->key_s = 0;
	ft_init_game2(game);
	return (game);
}

t_game	*ft_init_game2(t_game *game)
{
	game->player_x = 0;
	game->player_y = 0;
	game->player_position_set = 0;
	game->floor = -1;
	game->ceil = -1;
	game->dir_x = -1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
	game->ray = 0;
	return (game);
}
