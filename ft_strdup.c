/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:24:14 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/02 17:33:32 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
