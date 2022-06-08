/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:06:04 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/08 15:33:09 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strncmp(char *s1, char *s2, unsigned long long n)
{
	unsigned long long	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] && s2[i] && s1[i] == s2[i]) && i < n - 1)
		++i;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
