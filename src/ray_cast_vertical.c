/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_vertical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:17 by orezek            #+#    #+#             */
/*   Updated: 2024/06/26 12:30:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

point_t *get_vertical_ray_coordinates(game_t *game)
{
	point_t *ver_ray;
	ver_ray = malloc(sizeof(point_t));
	if (!ver_ray)
		return (NULL);
	int map_x = game->game_map.width;
	int map_y = game->game_map.height;
	int map_max_size;
	if (map_x < map_y)
		map_max_size = map_y;
	else
		map_max_size = map_x;
	char **map = game->game_map.map;
	double pa = game->player.player_angle; // 90
	double px = game->player.coordinates.x; // 600
	double py = game->player.coordinates.y; // 600

	int r, mx, my, dof;
	double rx, ry, ra, xo, yo;

	mx = 0; my = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = deg_to_rad(pa);
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		double nTan = tan(ra);

		// Look left (90 - 270 degrees)
		if (cos(ra) < -0.001)
		{
			rx = (((int) px >> 6) << 6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -SQUARE_SIZE;
			yo = -xo * nTan;
		}
		// Look right (270 - 90 degrees)
		else if (cos(ra) > 0.001)
		{
			rx = (((int) px >> 6) << 6) + 64;
			ry = (px - rx) * nTan + py;
			xo = SQUARE_SIZE;
			yo = -xo * nTan;
		}
		// Looking up or down (exactly vertical)
		else
		{
			rx = INFINITY;
			ry = INFINITY;
			dof = map_max_size;
		}
		while (dof < map_max_size)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			if (mx >= 0 && mx < map_x && my >= 0 && my < map_y && map[my][mx] == M_WALL)
				dof = map_max_size;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		ver_ray->x = rx;
		ver_ray->y = ry;
	}
	return (ver_ray);
}
