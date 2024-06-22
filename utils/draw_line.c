/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:03:23 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 19:26:30 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <math.h>
# include "../cube.h"

//Bresenham’s line algorithm
void draw_line(void *image, double startX, double startY, double endX, double endY, unsigned int color)
{
	mlx_image_t *img = (mlx_image_t *)image;
	int sXi; int sYi; int eXi; int eYi;
	sXi = round(startX);
	sYi = round(startY);
	eXi = round(endX);
	eYi = round(endY);


	int	dx = abs(eXi - sXi);
	int	dy = abs(eYi - sYi);
	int	sx = (sXi < eXi) ? 1 : -1;
	int	sy = (sYi < eYi) ? 1 : -1;
	int	err = dx - dy;

	while (true)
	{
		mlx_put_pixel(img, sXi, sYi, color);
		if (sXi == eXi && sYi == eYi)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			sXi += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			sYi += sy;
		}
	}
}
