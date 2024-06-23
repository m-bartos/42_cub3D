/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:26:00 by orezek            #+#    #+#             */
/*   Updated: 2024/06/23 16:52:08 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void	draw_rays(game_t *game)
{
	// Ray casting rendering
	// Only cast rays ,take player x, y and an angle cat rays in FOV in a way they end in the wall
	planes_t	*game_planes;
	double		fow;
	double		pa;

	fow = game->player_location.fow;
	pa = game->player_location.player_angle;
	game_planes = game->game_planes;
	for (int r = 0; r < fow; r++)
	{
		double h_distance = 0;
		double v_distance = 0;
		game->player_location.player_angle = fix_ang((pa - fow / 2) + r);
		point_t *hrc;
		point_t *vrc;
		hrc = get_horizontal_ray_coordinates_v1(game);
		vrc = get_vertical_ray_coordinates_v1(game);
		h_distance = get_point_distance(game, hrc);
		v_distance = get_point_distance(game, vrc);
		int ppp_color = get_rgba(0, 0, 0, 255);
		//unsigned int color = get_rgba(0, 255, 0, 255);
		if (v_distance < h_distance)
		{
			draw_line(game_planes->left_plane, game->player_location.player_coordinates.x, game->player_location.player_coordinates.y, vrc->x, vrc->y, ppp_color);
			//draw_line(game_planes.right_plane, pl.player_coordinates.x, pl.player_coordinates.y, vrc1->x, vrc1->y, color);
		}
		else
		{
			draw_line(game_planes->left_plane, game->player_location.player_coordinates.x, game->player_location.player_coordinates.y, hrc->x, hrc->y, ppp_color);
			//draw_line(game_planes.right_plane, pl.player_coordinates.x, pl.player_coordinates.y, hrc1->x, hrc1->y, color);
		}
	}
	game->player_location.player_angle = pa;
	printf("PA END: %f\n",game->player_location.player_angle);
	 // End of Ray Casting
	/////////////////////////////////////////////////////////////////////
}
