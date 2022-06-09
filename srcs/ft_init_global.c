/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_global.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:46 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 13:42:00 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_parameters(t_game *game, char *content)
{
	if (ft_read_parameters(game, content) != 1)
	{
		ft_error("Parameters read error\n");
		return (-1);
	}
	return (1);
}

int	ft_init_map(t_game *game, char *content)
{
	game->map = ft_strs_alloc();
	if (!game->map)
	{
		ft_error("Map allocation error\n");
		return (-1);
	}
	if (ft_read_map(game, content) != 1)
	{
		ft_error("Map read error\n");
		return (-1);
	}
	return (1);
}

int	ft_init_global(t_game *game, char *file)
{
	char	*content;

	content = ft_read_file(file);
	if (content == 0)
	{
		ft_error("File read error\n");
		return (0);
	}
	if (ft_init_parameters(game, content) != 1)
	{
		free(content);
		return (-1);
	}
	if (ft_init_map(game, content) != 1)
	{
		free(content);
		return (-2);
	}
	free(content);
	return (1);
}

int	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->mlx_win = mlx_new_window(game->mlx, \
						SCREEN_WIDTH, SCREEN_HEIGHT, "Cat3d");
	if (!game->mlx_win)
		return (-1);
	game->img = malloc(sizeof(t_data));
	if (!game->img)
		return (-2);
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img->img)
		return (-2);
	game->img->addr = mlx_get_data_addr(game->img->img, \
						&game->img->bits_per_pixel, &game->img->line_length, \
						&game->img->endian);
	if (!game->img->addr)
		return (-2);
	return (1);
}
