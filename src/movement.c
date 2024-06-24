/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 13:51:24 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
	game_t		*game;
	player_t	player_position;
	planes_t	*game_planes;
	double		pdx;
	double		pdy;

	game = (game_t *)param;
	player_position = (player_t) {0};

	// player_position.coordinates.x = game->player.coordinates.x;
	// player_position.coordinates.y = game->player.coordinates.y;
	// player_position.player_angle = game->player.player_angle;
	player_position = game->player;
	game_planes = game->game_planes;
	// initial player angle
	//int	pa;
	//pa = game->player.player_angle;
	pdx = cos(deg_to_rad(player_position.player_angle));
	pdy = sin(deg_to_rad(player_position.player_angle));

	// starting player coordinates
	static double x = 600;
	static double y = 600;
	// delta x and y

	printf("INIT:PA: %f\n", player_position.player_angle);

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
		player_position.coordinates.x += pdy * 5;
		player_position.coordinates.y += pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		x -= pdy * 5;
		y -= pdx * 5;
		player_position.coordinates.x -= pdy * 5;
		player_position.coordinates.y -= pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		x += pdx * 5;
		y -= pdy * 5;
		player_position.coordinates.x += pdx *5;
		player_position.coordinates.y -= pdy *5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		x -= pdx * 5;
		y += pdy * 5;
		player_position.coordinates.x -= pdx *5;
		player_position.coordinates.y += pdy *5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{
		// pa += 5;
		// pa = fix_ang(pa);
		// pdx = cos(deg_to_rad(pa));
		// pdy = sin(deg_to_rad(pa));
		player_position.player_angle += fix_ang(5);
		pdx = cos(deg_to_rad(player_position.player_angle));
		pdy = sin(deg_to_rad(player_position.player_angle));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{
		// pa -= 5;
		// pa = fix_ang(pa);
		// pdx = cos(deg_to_rad(pa));
		// pdy = sin(deg_to_rad(pa));
		player_position.player_angle -= fix_ang(5);
		pdx = cos(deg_to_rad(player_position.player_angle));
		pdy = sin(deg_to_rad(player_position.player_angle));
	}
	// implement FOV
////////////////////////////////////////////////////////
// Ray casting and Wall rendering

	// Connect key changes to the game struct
	// game->player.player_angle = pa;
	// game->player.coordinates.x = x;
	// game->player.coordinates.y = y;
	(void)x;
	(void)y;
	// New connection
	// game->player.player_angle = player_position.player_angle;
	// game->player.coordinates.x = player_position.coordinates.x;
	// game->player.coordinates.y = player_position.coordinates.y;

	game->player = player_position;

	draw_rays(game);
	draw_player(game);
	draw_wall(game);
}
