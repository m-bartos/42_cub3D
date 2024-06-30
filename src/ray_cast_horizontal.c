/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:09 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:21:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	init_hrc(t_game *game, t_hrc *h)
{
	h->hor_ray = malloc(sizeof(t_point));
	if (!h->hor_ray)
		exit(1);
	h->map_x = game->map->width;
	h->map_y = game->map->height;
	if (h->map_x < h->map_y)
		h->map_max_size = h->map_y;
	else
		h->map_max_size = h->map_x;
	h->pa = game->player->angle;
	h->px = game->player->coordinates.x;
	h->py = game->player->coordinates.y;
	h->map = game->map->map;
	h->ra = deg_to_rad(h->pa);
	h->a_tan = 1.0 / tan(h->ra);
}

static void	get_horizontal_intersection(t_hrc *h)
{
	while (h->dof < h->map_max_size)
	{
		h->mx = (int)(h->rx) / SQUARE_SIZE;
		h->my = (int)(h->ry) / SQUARE_SIZE;
		if (h->mx >= 0 && h->mx < h->map_x && h->my >= 0
			&& h->my < h->map_y && h->map[h->my][h->mx] == M_WALL)
			h->dof = h->map_max_size;
		else
		{
			h->rx += h->xo;
			h->ry += h->yo;
			h->dof += 1;
		}
	}
}

static void	calculate_horizontal_coordiantes(t_hrc *h)
{
	if (sin(h->ra) > 0.001)
	{
		h->ry = (floor(h->py / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
		h->rx = (h->py - h->ry) * h->a_tan + h->px;
		h->yo = -SQUARE_SIZE;
		h->xo = -h->yo * h->a_tan;
	}
	else if (sin(h->ra) < -0.001)
	{
		h->ry = (floor(h->py / SQUARE_SIZE) * SQUARE_SIZE) + SQUARE_SIZE;
		h->rx = (h->py - h->ry) * h->a_tan + h->px;
		h->yo = SQUARE_SIZE;
		h->xo = -h->yo * h->a_tan;
	}
	else
	{
		h->rx = INFINITY;
		h->ry = INFINITY;
		h->dof = h->map_max_size;
	}
}

t_point	*get_horizontal_ray_coordinates(t_game *game)
{
	t_hrc	h;

	h = (t_hrc){0};
	init_hrc(game, &h);
	calculate_horizontal_coordiantes(&h);
	get_horizontal_intersection(&h);
	h.hor_ray->x = h.rx;
	h.hor_ray->y = h.ry;
	return (h.hor_ray);
}
