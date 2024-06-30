/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:03:23 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:03:56 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	init_draw_line(t_draw_line *d, point_t start, point_t end)
{
	d->sxi = round(start.x);
	d->syi = round(start.y);
	d->exi = round(end.x);
	d->eyi = round(end.y);
	d->dx = abs(d->exi - d->sxi);
	d->dy = abs(d->eyi - d->syi);
}

static void	draw_pixels(mlx_image_t *image, t_draw_line *d, uint32_t color)
{
	while (true)
	{
		mlx_put_pixel(image, d->sxi, d->syi, color);
		if (d->sxi == d->exi && d->syi == d->eyi)
			break ;
		d->e2 = 2 * d->err;
		if (d->e2 > -d->dy)
		{
			d->err -= d->dy;
			d->sxi += d->sx;
		}
		if (d->e2 < d->dx)
		{
			d->err += d->dx;
			d->syi += d->sy;
		}
	}
}

void	draw_line(mlx_image_t *image, point_t start,
	point_t end, uint32_t color)
{
	t_draw_line	d;

	d = (t_draw_line){0};
	init_draw_line(&d, start, end);
	if (d.sxi < d.exi)
		d.sx = 1;
	else
		d.sx = -1;
	if (d.syi < d.eyi)
		d.sy = 1;
	else
		d.sy = -1;
	d.err = d.dx - d.dy;
	draw_pixels(image, &d, color);
}
