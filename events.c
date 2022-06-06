/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:47:40 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/03 19:08:14 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_event_keydown(int keycode, void *data)
{
	t_game	*game;

	game = (t_game*) data;
	
	switch (keycode)
	{
		case KEY_A:
			game->key_a = 1;
		break ;
		case KEY_D:
			game->key_d = 1;
		break ;
		case KEY_W:
			game->key_w = 1;
		break ;
		case KEY_S:
			game->key_s = 1;
		break ;
	}
	return (0);
}

int		ft_event_keyup(int keycode, void *data)
{
	t_game	*game;

	game = (t_game*) data;
	
	switch (keycode)
	{
		case KEY_A:
			game->key_a = 0;
		break ;
		case KEY_D:
			game->key_d = 0;
		break ;
		case KEY_W:
			game->key_w = 0;
		break ;
		case KEY_S:
			game->key_s = 0;
		break ;
	}
	return (0);
}