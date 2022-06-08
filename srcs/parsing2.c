/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:47:13 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 23:03:18 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_write_player_position(t_game *game, char direction, int x, int y)
{
	game->player_x = x + 0.5;
	game->player_y = y + 0.5;
	game->player_position_set = 1;
	ft_rotate_camera(game, ft_rotate_camera_relative(direction));
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
			if (ft_write_map(&str[i - len], len, map) != 1)
				return (0);
			len = 0;
			y++;
		} else
		if (i + 1 >= ft_strlen(str))
		{
			if (ft_write_map(&str[i - len], len + 1, map) != 1)
				return (-1);
			break ;
		} else
			len++;
		i++;
	}
	return (1);
}

int	ft_check_closing(char **map, int x, int y)
{
	// printf("Check %d %d\n", x, y);
	
	// Void border only
	if (y == 0 || y + 1 >= ft_strs_len(map))
		return (0);
	if (x == 0 || x + 1 >= ft_strlen(map[y]))
		return (-1);
	if ((x >= ft_strlen(map[y + 1]) || map[y + 1][x] == ' ') || (x >= ft_strlen(map[y - 1]) || map[y - 1][x] == ' '))
		return (-2);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (-3);
	return (1);
}

int	ft_check_closed(char **map)
{
	int i;
	int j;
	
	i = 0;
	while (i < ft_strs_len(map))
	{
		j = 0;	
		while (map[i][j])
		{
			// printf("[%c] %d %d , ", map[i][j], i, j);
			if (map[i][j] != '1' && map[i][j] != ' ' && ft_check_closing(map, j, i) != 1)
				return (-1);
			j++;
		}
		// printf("\n");
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
				ft_strs_rev(game->map);
				if (ft_read_player_position(game) != 1)
					return (-1);
				if (ft_check_closed(game->map) != 1)
					return (-2);
				return (1);
			}
			len = 0;
		} else
			len++;
		i++;
	}
	return (-2);
}
