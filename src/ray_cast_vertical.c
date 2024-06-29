/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_vertical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:17 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 20:03:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

typedef struct s_vrc
{
	point_t *ver_ray;
	int		map_x;
	int		map_y;
	int		map_max_size;
	double	pa;
	double	px;
	double	py;
	char	**map;
	int		mx;
	int		my;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	n_tan;
}	t_vrc;

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

// static void	get_vertical_intersection(t_vrc *v)
// {
// 	;
// }

// static void	calculate_horizontal_coordiantes(t_vrc *v)
// {
// 	;
// }
point_t *get_vertical_ray_coordinates(game_t *game)
{
	t_vrc	v;
	v = (t_vrc){0};
	init_vrc(game, &v);


	//point_t *ver_ray;
	//ver_ray = malloc(sizeof(point_t));
	//if (!ver_ray)
		//return (NULL);
	//int map_x = game->map->width;
	//int map_y = game->map->height;
	//int map_max_size;
	//if (map_x < map_y)
		//map_max_size = map_y;
	//else
		//map_max_size = map_x;
	char **map = game->map->map;
	double pa = game->player->angle; // 90
	double px = game->player->coordinates.x; // 600
	double py = game->player->coordinates.y; // 600

	int mx, my, dof; //r
	double rx, ry, ra, xo, yo;

	mx = 0; my = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = deg_to_rad(pa);
	dof = 0;
	double nTan = tan(ra);

	// Look left (90 - 270 degrees)
	if (cos(ra) < -0.001)
	{
		rx = (floor(px / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
		ry = (px - rx) * nTan + py;
		xo = -SQUARE_SIZE;
		yo = -xo * nTan;
	}
	// Look right (270 - 90 degrees)
	else if (cos(ra) > 0.001)
	{
		rx = (floor(px / SQUARE_SIZE) * SQUARE_SIZE) + 64;
		ry = (px - rx) * nTan + py;
		xo = SQUARE_SIZE;
		yo = -xo * nTan;
	}
	// Looking up or down (exactly vertical)
	else
	{
		rx = INFINITY;
		ry = INFINITY;
		dof = v.map_max_size;
	}
	while (dof < v.map_max_size)
	{
		mx = (int) (rx) / SQUARE_SIZE;
		my = (int) (ry) / SQUARE_SIZE;
		if (mx >= 0 && mx < v.map_x && my >= 0 && my < v.map_y && map[my][mx] == M_WALL)
			dof = v.map_max_size;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	v.ver_ray->x = rx;
	v.ver_ray->y = ry;
	return (v.ver_ray);
}
