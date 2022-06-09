/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 13:17:31 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_render_next_frame(void *data)
{
	t_game	*game;

	game = (t_game *) data;
	if (game->key_a)
	{
		ft_rotate_camera(game, ROTATION_SPEED);
		ft_draw_all((t_game *) data);
	}
	if (game->key_d)
	{
		ft_rotate_camera(game, -ROTATION_SPEED);
		ft_draw_all((t_game *) data);
	}
	ft_render_next_frame2(game, data);
	return (0);
}

int	ft_render_next_frame2(t_game *game, void *data)
{
	if (game->key_w)
	{
		if (!ft_iswall(game, (int)(game->player_x + \
					(game->dir_x * (MOVE_SPEED * 2))), (int)game->player_y))
			game->player_x += game->dir_x * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, \
					(int)(game->player_y + game->dir_y * (MOVE_SPEED * 2))))
			game->player_y += game->dir_y * MOVE_SPEED;
		ft_draw_all((t_game *) data);
	}
	if (game->key_s)
	{
		if (!ft_iswall(game, (int)(game->player_x - \
					(game->dir_x * (MOVE_SPEED * 2))), (int)game->player_y))
			game->player_x -= game->dir_x * MOVE_SPEED;
		if (!ft_iswall(game, (int)game->player_x, \
					(int)(game->player_y - game->dir_y * (MOVE_SPEED * 2))))
			game->player_y -= game->dir_y * MOVE_SPEED;
		ft_draw_all((t_game *) data);
	}
	return (0);
}

void	ft_draw_all(t_game *game)
{
	t_raycasting	*ray;

	ray = malloc(sizeof(t_raycasting));
	if (!ray)
	{
		ft_free_game(game);
		exit(0);
	}
	draw_rays_3d(game, ray);
	free(ray);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	return ;
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

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		ft_error("The program only takes the map file in first argument\n");
		return (0);
	}
	if (!check_filename(av[1]))
	{
		ft_error("The map filename must have .cub extension\n");
		return (-1);
	}
	game = ft_init_game();
	ft_check_init(av, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, ft_event_keydown, game);
	mlx_hook(game->mlx_win, 3, 1L << 0, ft_event_keyup, game);
	mlx_loop_hook(game->mlx, ft_render_next_frame, game);
	ft_draw_all(game);
	mlx_loop(game->mlx);
	return (0);
}
