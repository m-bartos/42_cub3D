/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:26:00 by orezek            #+#    #+#             */
/*   Updated: 2024/06/26 10:17:57 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void	draw_rays(game_t *game)
{
	planes_t	*game_planes;
	double		fov;
	double		pa;
	point_t		*hrc;
	point_t		*vrc;
	double h_distance = 0;
	double v_distance = 0;

	fov = game->player.fov;
	pa = game->player.player_angle;
	game_planes = game->game_planes;
	for (int r = 0; r < fov; r++)
	{

		game->player.player_angle = fix_ang((pa - fov / 2) + r);
		hrc = get_horizontal_ray_coordinates(game);
		vrc = get_vertical_ray_coordinates(game);
		h_distance = get_point_distance(game, hrc);
		v_distance = get_point_distance(game, vrc);
		if (v_distance < h_distance)
			draw_line(game_planes->mini_plane, game->player.coordinates.x, game->player.coordinates.y, vrc->x, vrc->y, RAY);
		else
			draw_line(game_planes->mini_plane, game->player.coordinates.x, game->player.coordinates.y, hrc->x, hrc->y, RAY);
	}
	game->player.player_angle = pa;
}
