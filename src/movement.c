/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 12:19:21 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
	game_t	*game;
	game = (game_t *)param;
	// starting player coordinates
	static double x = 600;
	static double y = 600;
	// delta x and y
	double pdx;
	double pdy;
	// initial player angle
	static int pa = 45;

	pdx = cos(deg_to_rad(pa));
	pdy = sin(deg_to_rad(pa));
	planes_t *game_planes = game->game_planes;

////////////////////////////////////////////////////////////////////////////////
// Cleaning initial or previous screen

	set_img_background(game_planes->left_plane, L_BACKGROUND);
	set_img_background(game_planes->right_plane, R_BACKGROUND);
	draw_map_char(game_planes->left_plane, game);

////////////////////////////////////////////////////////////////////////////////
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
	{
		x += pdy * 5;
		y += pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		x -= pdy * 5;
		y -= pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		x += pdx * 5;
		y -= pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		x-= pdx * 5;
		y+= pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{
		pa += 5;
		pa = fix_ang(pa);
		pdx = cos(deg_to_rad(pa));
		pdy = sin(deg_to_rad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{
		pa -= 5;
		pa = fix_ang(pa);
		pdx = cos(deg_to_rad(pa));
		pdy = sin(deg_to_rad(pa));
	}
	// implement FOV
////////////////////////////////////////////////////////
// Ray casting and Wall rendering

	// Connect key changes to the game struct
	game->player.player_angle = pa;
	game->player.player_coordinates.x = x;
	game->player.player_coordinates.y = y;
	draw_rays(game);
	draw_player(game);
	draw_wall(game);
}
