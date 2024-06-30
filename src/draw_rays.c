/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:26:00 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 23:45:43 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// Change planes->minigame to current minigame mlx_imgae

static void	put_rays_to_image(t_game *game, t_draw_ray *d_wall)
{
	uint32_t ray = get_rgba(0, 0, 0, 255);
	if (d_wall->v_distance < d_wall->h_distance)
		draw_line(d_wall->planes->mini_plane,
			(t_point){.x = game->player->coordinates.x, .y
			= game->player->coordinates.y},
			(t_point){.x = d_wall->vrc->x, .y = d_wall->vrc->y}, ray);
	else
		draw_line(d_wall->planes->mini_plane,
			(t_point){.x = game->player->coordinates.x, .y
			= game->player->coordinates.y},
			(t_point){.x = d_wall->hrc->x, .y = d_wall->hrc->y}, ray);
}

void	draw_rays(t_game *game)
{
	t_draw_ray	d_wall;

	d_wall = (t_draw_ray){0};
	d_wall.fov = game->player->fov;
	d_wall.pa = game->player->angle;
	d_wall.planes = game->planes;
	while (d_wall.r < d_wall.fov)
	{
		game->player->angle = fix_ang
			((d_wall.pa - d_wall.fov / 2) + d_wall.r);
		d_wall.hrc = get_horizontal_ray_coordinates(game);
		d_wall.vrc = get_vertical_ray_coordinates(game);
		d_wall.h_distance = get_point_distance(game, d_wall.hrc);
		d_wall.v_distance = get_point_distance(game, d_wall.vrc);
		put_rays_to_image(game, &d_wall);
		d_wall.r++;
	}
	game->player->angle = d_wall.pa;
}
