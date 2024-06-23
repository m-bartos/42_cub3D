/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:09 by orezek            #+#    #+#             */
/*   Updated: 2024/06/23 16:55:30 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

// args: map, px, py, pa
// returns: rx, ry

point_t *get_horizontal_ray_coordinates(player_location_t *pl, int map[18][15])
{
	point_t *hor_ray;
	hor_ray = malloc(sizeof(point_t));
	if (!hor_ray)
		return (NULL);
	// Casting ray
	// Temp map size
	int map_x = 50;
	int map_y = 50;

	int pa = pl->player_angle; // Initial player angle and position
	double px = pl->player_coordinates.x; //150
	double py = pl->player_coordinates.y; // 400
	// double pdx = cos(deg_to_rad(pa));
	// double pdy = sin(deg_to_rad(pa));

	int r, mx, my, mp, dof;
	double rx, ry, ra, xo, yo;
	//double v_distance = 0;
	// init the variables
	mx = 0; my = 0; mp = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = deg_to_rad(pa);


	// Horizontal lines
	// no of lines
	for (r = 0; r < 1; r++)
	{
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
			dof = 18;
		}
		while (dof < 18)
		{
			mx = (int) (rx)>>6;
			my = (int) (ry)>>6;
			mp = my * map_x + mx;
			(void) mp;
			if (mx >= 0 && mx < map_x && my >= 0 && my < map_y && map[my][mx] == 1)
				dof = 18;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		hor_ray->x = rx;
		hor_ray->y = ry;
	}
	return (hor_ray);
}


point_t	*get_horizontal_ray_coordinates_v1(game_t *game)
{
	point_t *hor_ray;
	hor_ray = malloc(sizeof(point_t));
	if (!hor_ray)
		return (NULL);
	// Casting ray
	// Temp map size
	int map_x = game->game_map.width;
	int map_y = game->game_map.height;

	int pa = game->player_location.player_angle;
	double px = game->player_location.player_coordinates.x;
	double py = game->player_location.player_coordinates.y;
	char **map = game->game_map.map;
	// double pdx = cos(deg_to_rad(pa));
	// double pdy = sin(deg_to_rad(pa));

	int r, mx, my, mp, dof;
	double rx, ry, ra, xo, yo;
	//double v_distance = 0;
	// init the variables
	mx = 0; my = 0; mp = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = deg_to_rad(pa);


	// Horizontal lines
	// no of lines
	for (r = 0; r < 1; r++)
	{
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
			dof = 18;
		}
		while (dof < 18)
		{
			mx = (int) (rx)>>6;
			my = (int) (ry)>>6;
			mp = my * map_x + mx;
			(void) mp;
			if (mx >= 0 && mx < map_x && my >= 0 && my < map_y && map[my][mx] == '1')
				dof = 18;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		hor_ray->x = rx;
		hor_ray->y = ry;
	}
	return (hor_ray);
}
