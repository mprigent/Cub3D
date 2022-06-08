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
		if (!ft_str_writeon(&buffer, buf))
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
		if (ft_str_cwriteon(&ret, *line++) != 1)
		{
			if (ret)
			{
				free(ret);
				return (NULL);
			}
		}
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

int	ft_is_identifier(char *str)
{
	if (ft_str_startswith(str, "NO")
		|| ft_str_startswith(str, "SO")
		|| ft_str_startswith(str, "WE")
		|| ft_str_startswith(str, "EA")
		|| ft_str_startswith(str, "F")
		|| ft_str_startswith(str, "C"))
		return (1);
	return (0);
}

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
	if (!ft_str_startswith(&config[begin], "1")
		&& !ft_str_startswith(&config[begin], " "))
		return (-2);
	return (1);
}
