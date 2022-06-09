/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:05:24 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 16:26:03 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_read_parameter(t_game *game, char *config, int begin, int len)
{
	char	*value;

	if (ft_str_isempty(config, begin, len))
		return (1);
	if (ft_is_identifier(&config[begin]))
	{
		value = ft_read_value(&config[begin], len);
		if (value == NULL)
			return (0);
		if (ft_str_contains(value, (char) 32))
		{
			free(value);
			return (-1);
		}
		ft_apply_value(game, &config[begin], value);
		return (1);
	}
	if (!ft_str_startswith(&config[begin], "1", 0)
		&& !ft_str_startswith(&config[begin], " ", 0))
		return (-2);
	return (1);
}

char	*ft_read_file(char *file)
{
	char	*buffer;
	int		ret;
	char	buf[2];
	int		fd;

	buffer = NULL;
	fd = open(file, O_RDWR);
	if (fd <= -1)
	{
		ft_error("File error\n");
		exit(1);
	}
	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, 1);
		if (ret == -1)
			return (free(buffer), NULL);
		buf[1] = 0;
		if (!ft_str_writeon(&buffer, buf))
			return (free(buffer), NULL);
	}
	return (buffer);
}

int	ft_read_parameters(t_game *game, char *config)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (config[i])
	{
		if (config[i] == '\n')
		{
			if (ft_read_parameter(game, config, i - len, len) != 1)
				return (0);
			len = 0;
		}
		else
			len++;
		i++;
	}
	if (ft_check_for_missing(game) != 1)
		return (-1);
	return (1);
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
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
					|| game->map[y][x] == 'E'
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
