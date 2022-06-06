/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:06:54 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/06 17:19:57 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_texture	*ft_texture(void *mlx, char *filename)
{
	t_texture *ret;

	ret = malloc(sizeof(t_texture));
	if (!ret)
		return (0);
	ret->width = 0;
	ret->height = 0;
	ret->data = 0;
	ret->data = mlx_xpm_file_to_image(mlx, filename, &ret->width, &ret->height);
	if (!ret->data)
		return (0);
	return (ret);
}