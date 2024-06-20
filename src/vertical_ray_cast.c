/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray_cast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:18:17 by orezek            #+#    #+#             */
/*   Updated: 2024/06/20 13:33:46 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

point_t *get_vertical_ray_coordinates(player_location_t *pl, int map[18][15])
{
	point_t *ver_ray;
	ver_ray = malloc(sizeof(point_t));
	if (!ver_ray)
		return (NULL);
	// Temp map size
	int map_x = 50;
	int map_y = 50;

	int pa = pl->player_angle; // Initial player angle and position
	double px = pl->player_coordinates.x; //150
	double py = pl->player_coordinates.y; // 400
	// double pdx = cos(degToRad(pa));
	// double pdy = sin(degToRad(pa));

	int r, mx, my, mp, dof;
	double rx, ry, ra, xo, yo;
	//double v_distance = 0;
	// init the variables
	mx = 0; my = 0; mp = 0; dof = 0;
	rx = 0; ry = 0; ra = 0; xo = 0; yo = 0;
	// ray angle = player angle
	ra = degToRad(pa);

	for (r = 0; r < 1; r++)
	{
		dof = 0;
		double nTan = tan(ra);

		// Look left (90 - 270 degrees)
		if (cos(ra) < -0.001) {
			rx = (((int) px >> 6) << 6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		// Look right (270 - 90 degrees)
		else if (cos(ra) > 0.001) {
			rx = (((int) px >> 6) << 6) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		// Looking up or down (exactly vertical)
		else if (ra == M_PI / 2 || ra == 3 * M_PI / 2) {
			rx = px;
			ry = py;
			dof = 18;
		}
		while (dof < 18)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * map_x + mx;
			if (mp < map_x * map_y && map[my][mx] == 1) { // Corrected index access
				dof = 18;
			} else
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