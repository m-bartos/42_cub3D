/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 14:14:29 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
///////////////////////////////////////////////////////////////////////////////
// Declare and initialize variables
	game_t		*game;
	player_t	*player;
	double		pdx;
	double		pdy;

	game = (game_t *)param;
	player = &game->player;
	pdx = cos(deg_to_rad(player->player_angle));
	pdy = sin(deg_to_rad(player->player_angle));
////////////////////////////////////////////////////////////////////////////////
// Clean initial or previous screen

	set_img_background(game->game_planes->left_plane, L_BACKGROUND);
	set_img_background(game->game_planes->right_plane, R_BACKGROUND);
	draw_map_char(game->game_planes->left_plane, game);

////////////////////////////////////////////////////////////////////////////////
// Update player coordinates based on key presses - key press == 5px change in position
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
	{
		player->coordinates.x += pdy * KEY_PRESS;
		player->coordinates.y += pdx * KEY_PRESS;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		player->coordinates.x -= pdy * KEY_PRESS;
		player->coordinates.y -= pdx * KEY_PRESS;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		player->coordinates.x += pdx * KEY_PRESS;
		player->coordinates.y -= pdy * KEY_PRESS;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		player->coordinates.x -= pdx * KEY_PRESS;
		player->coordinates.y += pdy * KEY_PRESS;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{

		player->player_angle += fix_ang(KEY_PRESS);
		pdx = cos(deg_to_rad(player->player_angle));
		pdy = sin(deg_to_rad(player->player_angle));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{

		player->player_angle -= fix_ang(KEY_PRESS);
		pdx = cos(deg_to_rad(player->player_angle));
		pdy = sin(deg_to_rad(player->player_angle));
	}
////////////////////////////////////////////////////////
// Ray casting and Wall rendering
	draw_rays(game);
	draw_player(game);
	draw_wall(game);
}
