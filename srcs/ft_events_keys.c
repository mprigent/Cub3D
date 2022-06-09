/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:47:40 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 15:22:45 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_event_keydown(int keycode, void *data)
{
	t_game	*game;

	game = (t_game *) data;
	if (keycode == KEY_A)
		game->key_a = 1;
	if (keycode == KEY_D)
		game->key_d = 1;
	if (keycode == KEY_W)
		game->key_w = 1;
	if (keycode == KEY_S)
		game->key_s = 1;
	if (keycode == KEY_LEFT)
		game->key_left = 1;
	if (keycode == KEY_RIGHT)
		game->key_right = 1;
	return (0);
}

int	ft_event_keyup(int keycode, void *data)
{
	t_game	*game;

	game = (t_game *) data;
	if (keycode == KEY_A)
		game->key_a = 0;
	if (keycode == KEY_D)
		game->key_d = 0;
	if (keycode == KEY_W)
		game->key_w = 0;
	if (keycode == KEY_S)
		game->key_s = 0;
	if (keycode == KEY_LEFT)
		game->key_left = 0;
	if (keycode == KEY_RIGHT)
		game->key_right = 0;
	if (keycode == ESCAPE)
	{
		ft_free_game(game);
		exit(0);
	}
	return (0);
}

int	ft_event_close(void *data)
{
	ft_free_game((t_game *) data);
	exit(0);
}