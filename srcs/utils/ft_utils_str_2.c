/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:15:24 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 19:26:19 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**ft_strs_alloc(void)
{
	char	**dst;

	dst = malloc(sizeof(char *));
	if (!dst)
		return (0);
	dst[0] = 0;
	return (dst);
}

int	ft_strs_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_strs_free(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

static char	**ft_strs_allocate(char *str)
{
	char	**dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char *) * 2);
	if (!dst)
		return (NULL);
	dst[0] = ft_strdup(str);
	if (!dst[0])
	{
		free(dst);
		return (NULL);
	}
	dst[1] = NULL;
	return (dst);
}

static int	ft_strs_copy_into(char **tab, char **dst)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		dst[i] = ft_strdup(tab[i]);
		if (!dst[i])
			return (0);
		i++;
	}
	dst[i] = 0;
	return (1);
}
