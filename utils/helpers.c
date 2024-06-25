/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:40:42 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 19:19:02 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}

int	fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

u_int32_t	get_rgba(u_int32_t r, u_int32_t g, u_int32_t b, u_int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
