/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_vertical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:17 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 20:34:32 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	init_vrc(game_t *game, t_vrc *v)
{
	v->ver_ray = malloc(sizeof(point_t));
	if (!v->ver_ray)
		exit(1);
	v->map_x = game->map->width;
	v->map_y = game->map->height;
	if (v->map_x < v->map_y)
		v->map_max_size = v->map_y;
	else
		v->map_max_size = v->map_x;
	v->pa = game->player->angle;
	v->px = game->player->coordinates.x;
	v->py = game->player->coordinates.y;
	v->map = game->map->map;
	v->ra = deg_to_rad(v->pa);
	v->n_tan = tan(v->ra);
}

static void	get_vertical_intersection(t_vrc *v)
{
	while (v->dof < v->map_max_size)
	{
		v->mx = (int)(v->rx) / SQUARE_SIZE;
		v->my = (int)(v->ry) / SQUARE_SIZE;
		if (v->mx >= 0 && v->mx < v->map_x && v->my >= 0
			&& v->my < v->map_y && v->map[v->my][v->mx] == M_WALL)
			v->dof = v->map_max_size;
		else
		{
			v->rx += v->xo;
			v->ry += v->yo;
			v->dof += 1;
		}
	}
}

static void	calculate_vertical_coordiantes(t_vrc *v)
{
	if (cos(v->ra) < -0.001)
	{
		v->rx = (floor(v->px / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
		v->ry = (v->px - v->rx) * v->n_tan + v->py;
		v->xo = -SQUARE_SIZE;
		v->yo = -v->xo * v->n_tan;
	}
	else if (cos(v->ra) > 0.001)
	{
		v->rx = (floor(v->px / SQUARE_SIZE) * SQUARE_SIZE) + 64;
		v->ry = (v->px - v->rx) * v->n_tan + v->py;
		v->xo = SQUARE_SIZE;
		v->yo = -v->xo * v->n_tan;
	}
	else
	{
		v->rx = INFINITY;
		v->ry = INFINITY;
		v->dof = v->map_max_size;
	}
}

point_t	*get_vertical_ray_coordinates(game_t *game)
{
	t_vrc	v;

	v = (t_vrc){0};
	init_vrc(game, &v);
	calculate_vertical_coordiantes(&v);
	get_vertical_intersection(&v);
	v.ver_ray->x = v.rx;
	v.ver_ray->y = v.ry;
	return (v.ver_ray);
}
