/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:47:13 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/06 16:12:08 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_write_player_position(t_game *game, char direction, int x, int y)
{
	game->player_x = x + 0.5;
	game->player_y = y + 0.5;
	game->player_position_set = 1;
}

int	ft_read_player_position(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < ft_strs_len(game->map))
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E'
					|| game->map[y][x] == 'W')
			{
				if (game->player_position_set == 1)
					return (0);
				ft_write_player_position(game, game->map[y][x], x, y);
			}
			x++;
		}
		y++;
	}
	if (game->player_position_set)
		return (1);
	return (-1);
}

int	ft_read_map_is_valid(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != (char) 32 && str[i] != 'N'
				&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
					return (0);
		i++;
	}
	return (1);
}

int	ft_write_map(char *str, int len, char ***map, int y)
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

int	ft_read_map_content(char *str, char ***map)
{
	int		len;
	int		y;
	int		i;

	i = 0;
	y = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (ft_write_map(&str[i - len], len, map, y++) != 1)
				return (0);
			len = 0;
		} else
		if (i + 1 >= ft_strlen(str))
		{
			if (ft_write_map(&str[i - len], len + 1, map, y) != 1)
				return (-1);
			break ;
		} else
			len++;
		i++;
	}
	return (1);
}

int	ft_read_map(t_game *game, char *config)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (config[i])
	{
		if (config[i] == '\n' && i + 1 < ft_strlen(config))
		{
			if (ft_str_startswith(&config[i - len], " ") || ft_str_startswith(&config[i - len], "1"))
			{
				if (ft_read_map_content(&config[i - len], &(game->map)) != 1)
					return (0);
				if (ft_read_player_position(game) != 1)
					return (-1);
				return (1);
			}
			len = 0;
		} else
			len++;
		i++;
	}
	return (-2);
}
