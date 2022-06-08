/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_maths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprigent <mprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:55:50 by mprigent          #+#    #+#             */
/*   Updated: 2022/06/08 19:57:41 by mprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	ft_dist(float ax, float ay, float bx, float by, float ang)
{
	(void) ang;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float degToRad(float a)
{
	return a*M_PI/180.0;
}

float FixAng(float a)
{
	if (a > 359) { a -= 360;}
	if (a < 0) { a += 360;} 
	return a;
}

float distance(float ax, float ay, float bx, float by, float ang)
{
	return cos(degToRad(ang))*(bx-ax) - sin(degToRad(ang))*(by-ay);
}