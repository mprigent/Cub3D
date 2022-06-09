/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:47:13 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/09 16:26:18 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_read_value(char *line, int len)
{
	char	*ret;

	ret = NULL;
	while (*line && *line != (char) 32)
	{
		line++;
		len--;
	}
	while (*line && *line == (char) 32)
	{
		line++;
		len--;
	}
	while (*line && len--)
	{
		if (*line != ' ' && ft_str_cwriteon(&ret, *line) != 1 && ret)
		{
			free(ret);
			return (NULL);
		}
		line++;
	}
	return (ret);
}

int	ft_read_map_is_valid(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != (char) 32
			&& str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	ft_read_map_content(char *str, char ***map)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (ft_write_map(&str[i - len], len, map) != 1)
				return (0);
			len = 0;
		}
		else if (i + 1 >= ft_strlen(str))
		{
			if (ft_write_map(&str[i - len], len + 1, map) != 1)
				return (-1);
			break ;
		}
		else
			len++;
		i++;
	}
	return (1);
}

int	ft_read_map2(t_game *game, char *config, int i, int len)
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
			if (ft_str_startswith(&config[i - len], " ", 0)
				|| ft_str_startswith(&config[i - len], "1", 0))
			{
				i = ft_read_map2(game, config, i, len);
				return (i);
			}
			len = 0;
		}
		else
			len++;
		i++;
	}
	return (-2);
}
