/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:06:54 by gadeneux          #+#    #+#             */
/*   Updated: 2022/06/07 22:34:05 by gadeneux         ###   ########.fr       */
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

void	ft_free_texture(void *mlx_ptr, t_texture *texture)
{
	if (texture != 0)
		mlx_destroy_image(mlx_ptr, texture->data);
}