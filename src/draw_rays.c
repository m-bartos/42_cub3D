/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:26:00 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 13:18:19 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// Change game_planes->minigame to current minigame mlx_imgae

void	draw_rays(game_t *game)
{
	t_draw_ray	d_wall;

	d_wall = (t_draw_ray){0};
	d_wall.fov = game->player->fov;
	d_wall.pa = game->player->player_angle;
	d_wall.game_planes = game->game_planes;
	while (d_wall.r < d_wall.fov)
	{
		game->player->player_angle = fix_ang
			((d_wall.pa - d_wall.fov / 2) + d_wall.r);
		d_wall.hrc = get_horizontal_ray_coordinates(game);
		d_wall.vrc = get_vertical_ray_coordinates(game);
		d_wall.h_distance = get_point_distance(game, d_wall.hrc);
		d_wall.v_distance = get_point_distance(game, d_wall.vrc);
		if (d_wall.v_distance < d_wall.h_distance)
			draw_line(d_wall.game_planes->mini_plane,
				game->player->coordinates.x, game->player->coordinates.y,
				d_wall.vrc->x, d_wall.vrc->y, RAY);
		else
			draw_line(d_wall.game_planes->mini_plane,
				game->player->coordinates.x, game->player->coordinates.y,
				d_wall.hrc->x, d_wall.hrc->y, RAY);
		d_wall.r++;
	}
	game->player->player_angle = d_wall.pa;
}
