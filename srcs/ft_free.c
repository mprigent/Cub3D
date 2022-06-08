/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:26:01 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 20:26:34 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_game(t_game *game)
{
	if (game->mlx && game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->img)
		free(game->img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->map)
		ft_strs_free(&game->map);
	ft_free_texture(game->mlx, game->north);
	ft_free_texture(game->mlx, game->south);
	ft_free_texture(game->mlx, game->east);
	ft_free_texture(game->mlx, game->west);
	if (game->mlx)
		free(game->mlx);
}