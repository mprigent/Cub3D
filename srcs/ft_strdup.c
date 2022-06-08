/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:24:14 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 18:52:22 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup2(char *s1, int len)
{
	char	*dst;

	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	return (ft_memcpy(dst, s1, len));
}

char	*ft_strdup(char *s1)
{
	char	*dst;
	size_t	l;

	l = ft_strlen(s1);
	dst = ft_calloc(l + 1, sizeof(char));
	if (!dst)
		return (NULL);
	return (ft_memcpy(dst, s1, l));
}
