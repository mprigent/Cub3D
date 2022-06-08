/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 10:19:41 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 18:52:22 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;
	size_t	i;

	i = 0;
	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	dst = malloc((count * size));
	if (!dst)
		return (NULL);
	while (i < (count * size))
		((char *)dst)[i++] = 0;
	return (dst);
}
