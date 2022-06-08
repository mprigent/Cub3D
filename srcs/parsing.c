#include "../includes/cub3d.h"

char	*ft_read_file(char *file)
{
	char	*buffer;
	int		ret;
	char	*buf;
	int		fd;

	buffer = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buf = malloc(sizeof(char) * 2);
	if (!buf)
		return (NULL);
	while ((ret = read(fd, buf, 1)))
	{
		buf[1] = 0;
		if(!ft_str_writeon(&buffer, buf))
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
	}
	if (buf)
		free(buf);
	return (buffer);
}

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
		if (ft_str_cwriteon(&ret, *line) != 1)
			if (ret)
			{
				free(ret);
				return (NULL);
			}
		line++;
	}
	return (ret);
}

void	ft_apply_value(t_game *game, char *line, char *value)
{
	if (ft_str_startswith(line, "NO"))
		game->north = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "SO"))
		game->south = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "WE"))
		game->west = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "EA"))
		game->east = ft_texture(game->mlx, value);
	if (ft_str_startswith(line, "F"))
		game->floor = ft_rgb(value);
	if (ft_str_startswith(line, "C"))
		game->ceil = ft_rgb(value);
	free(value);
}

int	ft_read_parameter(t_game *game, char *config, int begin, int len)
{
	char	*value;
	if (ft_str_isempty(config, begin, len))
		return (1);

	if (ft_str_startswith(&config[begin], "NO") || ft_str_startswith(&config[begin], "SO")
			|| ft_str_startswith(&config[begin], "WE") || ft_str_startswith(&config[begin], "EA")
			|| ft_str_startswith(&config[begin], "F") || ft_str_startswith(&config[begin], "C"))
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

	if (!ft_str_startswith(&config[begin], "1") && !ft_str_startswith(&config[begin], " "))
		return (-2);

	return (1);
}

int	ft_check_for_missing(t_game *game)
{
	if (!game->north || !game->south || !game->west || !game->east)
		return (0);
	if (game->ceil < 0 || game->floor < 0)
		return (-1);
	return (1);
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
		} else
			len++;
		i++;
	}
	if (ft_check_for_missing(game) != 1)
		return (-1);
	return (1);
}