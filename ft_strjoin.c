/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:01:25 by gadeneux          #+#    #+#             */
/*   Updated: 2022/05/30 18:14:32 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		dl;

	if (!s1 || !s2)
		return (0);
	dl = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	dst = ft_calloc(dl, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcat(dst, s1, dl);
	ft_strlcat(dst, s2, dl);
	return (dst);
}
