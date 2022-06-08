/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:29 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 19:29:53 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_str_writeon(char **str, char *to_add)
{
	char	*res;

	if (!str)
		return (0);
	if (!(*str) || *str == NULL)
	{
		*str = ft_strdup(to_add);
		if (!*str || *str == NULL)
			return (-1);
		return (1);
	}
	res = ft_strjoin(*str, to_add);
	if (!res || res == NULL)
		return (-2);
	free(*str);
	*str = res;
	return (1);
}

int	ft_str_cwriteon(char **str, char c)
{
	char	*to_add;
	int		ret;

	if (!str)
		return (0);
	to_add = malloc(2 * sizeof(char));
	if (!to_add)
		return (-1);
	to_add[0] = c;
	to_add[1] = 0;
	ret = ft_str_writeon(str, to_add);
	free(to_add);
	return (ret);
}

int	ft_str_isempty(char *str, int begin, int len)
{
	int	i;

	if (!str)
		return (0);
	i = begin;
	while (str[i] && i < begin + len)
	{
		if (str[i] != (char)32)
			return (0);
		i++;
	}
	return (1);
}

int	ft_str_startswith(char *str, char *something)
{
	if (!str)
		return (0);
	if (!something)
		return (0);
	return (ft_strncmp(str, something, ft_strlen(something)) == 0);
}

int	ft_str_contains(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
