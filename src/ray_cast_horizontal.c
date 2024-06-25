/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:09 by orezek            #+#    #+#             */
/*   Updated: 2024/06/25 00:00:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

point_t	*get_horizontal_ray_coordinates(game_t *game)
{
	point_t *hor_ray;
	hor_ray = malloc(sizeof(point_t));
	if (!hor_ray)
		return (NULL);
	int map_x = game->game_map.width;
	int map_y = game->game_map.height;
	int map_max_size;
	if (map_x < map_y)
		map_max_size = map_y;
	else
		map_max_size = map_x;
	int pa = game->player.player_angle;
	double px = game->player.coordinates.x;
	double py = game->player.coordinates.y;
	char **map = game->game_map.map;

	int mx, my, dof;
	double rx, ry, ra, xo, yo;

	mx = 0; my = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = deg_to_rad(pa);


// Horizontal lines
// no of lines
	ra = deg_to_rad(pa);
	dof = 0;
	float aTan = 1.0 / tan(ra);
	// look up 0 - 180 right -> left right is 0
	if (sin(ra) > 0.001)
	{
		ry = (((int) py >> 6) << 6) - 0.0001;
		rx = (py - ry) * aTan + px;
		yo = -64;
		xo = -yo * aTan;
	}
	// look down 180 - 360
	else if (sin(ra) < -0.001)
	{
		ry = (((int) py >> 6) << 6) + 64;
		rx = (py - ry) * aTan+px;
		yo = 64;
		xo = -yo * aTan;
	}
	// look left or right - exactly horizontal
	else
	{
		rx = 100000;
		ry = 100000;
		dof = map_max_size;
	}
	while (dof < map_max_size)
	{
		mx = (int) (rx)>>6;
		my = (int) (ry)>>6;
		if (mx >= 0 && mx < map_x && my >= 0 && my < map_y && map[my][mx] == '1')
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
