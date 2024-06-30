/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:44 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:15:45 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_square(mlx_image_t *image, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQUARE_SIZE - 1)
	{
		j = 0;
		while (j < SQUARE_SIZE - 1)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	put_square(mlx_image_t *image, t_point location,
	int32_t size, u_int32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < size - 1)
		{
			mlx_put_pixel(image, location.x + i, location.y + j, color);
			j++;
		}
		i++;
	}
}
