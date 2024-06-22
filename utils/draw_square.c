/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:44 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 21:02:36 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_square(mlx_image_t *image, int x, int y, unsigned int color)
{
	for (int i = 0; i < SQUARE_SIZE - 1; i++)
	{
		for (int j = 0; j < SQUARE_SIZE - 1; j++)
		{
			mlx_put_pixel(image, x + i, y + j, color);
		}
	}
}

void	put_square(mlx_image_t *image , point_t location, int32_t size, u_int32_t color)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1; j++)
			mlx_put_pixel(image, location.x + i, location.y + j, color);
	}
}
