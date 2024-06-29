/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:09 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 19:01:17 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

typedef struct s_hrc
{
	point_t *hor_ray;
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
	double	a_tan;
}	t_hrc;

void	init_hrc(game_t *game, t_hrc *h)
{
	h->hor_ray = malloc(sizeof(point_t));
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


point_t	*get_horizontal_ray_coordinates(game_t *game)
{
	t_hrc	h;
	h = (t_hrc){0};
	init_hrc(game, &h);

	point_t *hor_ray;
	hor_ray = malloc(sizeof(point_t));
	if (!hor_ray)
		return (NULL);
	int map_x = game->map->width;
	int map_y = game->map->height;
	int map_max_size;
	if (map_x < map_y)
		map_max_size = map_y;
	else
		map_max_size = map_x;
	double pa = game->player->angle;
	double px = game->player->coordinates.x;
	double py = game->player->coordinates.y;
	char **map = game->map->map;

	int mx, my, dof;
	double rx, ry, ra, xo, yo;

	mx = 0; my = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;

// Horizontal lines
// no of lines
	ra = deg_to_rad(pa);
	dof = 0;
	float aTan = 1.0 / tan(ra);
	// look up 0 - 180
	if (sin(ra) > 0.001)
	{
		ry = (floor(py / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
		rx = (py - ry) * aTan + px;
		yo = -SQUARE_SIZE;
		xo = -yo * aTan;
	}
	// look down 180 - 360
	else if (sin(ra) < -0.001)
	{
		ry = (floor(py / SQUARE_SIZE) * SQUARE_SIZE) + SQUARE_SIZE;
		rx = (py - ry) * aTan+px;
		yo = SQUARE_SIZE;
		xo = -yo * aTan;
	}
	// look left or right - exactly horizontal
	else
	{
		rx = INFINITY;
		ry = INFINITY;
		dof = map_max_size;
	}
	while (dof < map_max_size)
	{
		mx = (int) (rx) / SQUARE_SIZE;
		my = (int) (ry) / SQUARE_SIZE;
		if (mx >= 0 && mx < map_x && my >= 0 && my < map_y && map[my][mx] == M_WALL)
			dof = map_max_size;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	hor_ray->x = rx;
	hor_ray->y = ry;
	return (hor_ray);
}
