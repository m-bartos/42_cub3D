/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_background.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:06:37 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 21:35:01 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	set_img_background(mlx_image_t *image, int32_t color)
{
	int	x;
	int	y;

	x = 0;
	while(x < (int) image->width)
	{
		y = 0;
		while (y < (int) image->height)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
