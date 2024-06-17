/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:03:23 by orezek            #+#    #+#             */
/*   Updated: 2024/06/17 19:54:23 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <math.h>
# include "../cube.h"

//Bresenham’s line algorithm
void draw_line(void *image, int startX, int startY, int endX, int endY, unsigned int color)
{
	mlx_image_t *img = (mlx_image_t *)image;

	int	dx = abs(endX - startX);
	int	dy = abs(endY - startY);
	int	sx = (startX < endX) ? 1 : -1;
	int	sy = (startY < endY) ? 1 : -1;
	int	err = dx - dy;

    while (1) {
        mlx_put_pixel(img, startX, startY, color);
        if (startX == endX && startY == endY) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            startX += sx;
        }
        if (e2 < dx) {
            err += dx;
            startY += sy;
        }
    }
}
