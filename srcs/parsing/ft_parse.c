/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:31:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 16:18:06 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_write_player_position(t_game *game, char direction, int x, int y)
{
	game->player_x = x + 0.5;
	game->player_y = y + 0.5;
	game->player_position_set = 1;
	ft_rotate_camera(game, ft_rotate_camera_relative(direction));
}

int	ft_write_map(char *str, int len, char ***map)
{
	char	*buf;

	if (ft_str_isempty(str, 0, len))
		return (0);
	if (ft_read_map_is_valid(str, len) != 1)
		return (-1);
	buf = ft_strdup2(str, len);
	if (!buf)
		return (-2);
	if (ft_strs_writeon(map, buf) != 1)
	{
		free(buf);
		return (-3);
	}
	free(buf);
	return (1);
}

void	ft_apply_value(t_game *game, char *line, char *value)
{
	if (ft_str_startswith(line, "NO", 1))
		game->north = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "SO", 1))
		game->south = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "WE", 1))
		game->west = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "EA", 1))
		game->east = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "F", 1))
		game->floor = ft_rgb(value);
	if (ft_str_startswith(line, "C", 1))
		game->ceil = ft_rgb(value);
	free(value);
}

int	ft_is_identifier(char *str)
{
	if (ft_str_startswith(str, "NO", 1)
		|| ft_str_startswith(str, "SO", 1)
		|| ft_str_startswith(str, "WE", 1)
		|| ft_str_startswith(str, "EA", 1)
		|| ft_str_startswith(str, "F", 1)
		|| ft_str_startswith(str, "C", 1))
		return (1);
	return (0);
}
