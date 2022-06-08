/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:41:16 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 18:52:22 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	if (!d && !s)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}
