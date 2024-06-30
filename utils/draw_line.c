/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:03:23 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 12:16:41 by orezek           ###   ########.fr       */
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

void	draw_line1(mlx_image_t *image, point_t start,
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

void draw_line(mlx_image_t *image, double startX, double startY, double endX, double endY, unsigned int color)
{
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
		mlx_put_pixel(image, sXi, sYi, color);
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
