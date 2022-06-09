/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:25:45 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/09 13:35:27 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strs_writeon(char ***tab, char *str)
{
	char	**dst;
	char	**buf;

	if (!*tab || !*tab || !*tab[0])
	{
		*tab = ft_strs_allocate(str);
		return (!!*tab);
	}
	dst = ft_calloc(sizeof(char *), ft_strs_len(*tab) + 2);
	if (!dst)
		return (-1);
	if (ft_strs_copy_into(*tab, dst) != 1)
	{
		ft_strs_free(&dst);
		return (-2);
	}
	dst[ft_strs_len(*tab)] = ft_strdup(str);
	if (!dst[ft_strs_len(*tab)])
		return (ft_strs_free(&dst), -3);
	buf = *tab;
	*tab = dst;
	ft_strs_free(&buf);
	return (1);
}

void	ft_strs_rev(char **strs)
{
	int		len;
	char	*a;
	char	*b;
	int		i;

	len = ft_strs_len(strs);
	i = 0;
	while (i < len / 2)
	{
		a = strs[i];
		b = strs[len - 1 - i];
		strs[i] = b;
		strs[len - 1 - i] = a;
		i++;
	}
}

int	is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

int	check_value(int i)
{
	return (i >= 0 && i <= 255);
}
