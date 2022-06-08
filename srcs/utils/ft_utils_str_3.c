/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:25:45 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 21:00:59 by mprigent         ###   ########.fr       */
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
		if (!*tab)
			return (0);
		return (1);
	}
	dst = malloc(sizeof(char *) * (ft_strs_len(*tab) + 2));
	if (!dst)
		return (-1);
	dst[0] = 0;
	if (ft_strs_copy_into(*tab, dst) != 1)
	{
		ft_strs_free(&dst);
		return (-2);
	}
	dst[ft_strs_len(*tab)] = ft_strdup(str);
	dst[ft_strs_len(*tab) + 1] = 0;
	if (!dst[ft_strs_len(*tab)])
	{
		ft_strs_free(&dst);
		return (-3);
	}
	buf = *tab;
	*tab = dst;
	ft_strs_free(&buf);
	return (1);
}

int	is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

int	check_value(int i)
{
	return (i >= 0 && i <= 255);
}
