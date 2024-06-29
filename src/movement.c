/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 17:02:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
/*

XA: 1.000000
YA: 0.000000
MAP_X: 9, MAP_Y: 9
X605.000000: Y600.000000:
Angle: 90.000000
X605.000000: Y600.000000:
Angle: 90.000000

XA: 1.000000
YA: 0.000000
MAP_X: 9, MAP_Y: 9
X620.000000: Y600.000000:
Angle: 270.000000
X620.000000: Y600.000000:
Angle: 270.000000

// These two are opposite
XA: 1.000000
YA: 0.000000
MAP_X: 9, MAP_Y: 9
X600.000000: Y605.000000:
Angle: 0.000000
X600.000000: Y605.000000:
Angle: 0.000000

XA: 1.000000
YA: 0.000000
MAP_X: 10, MAP_Y: 9
X700.000000: Y600.000000:
Angle: 180.000000
X700.000000: Y600.000000:
Angle: 180.000000

*/
void	move_player(mlx_key_data_t key, void *param)
{
///////////////////////////////////////////////////////////////////////////////
// Declare and initialize variables
	game_t		*game;
	player_t	*player;
	double		pdx;
	double		pdy;

	game = (game_t *)param;
	player = game->player;
	pdx = cos(deg_to_rad(player->angle));
	pdy = sin(deg_to_rad(player->angle));
////////////////////////////////////////////////////////////////////////////////
// Clean initial or previous screen
	set_img_background(game->planes->game_plane, R_BACKGROUND);
////////////////////////////////////////////////////////////////////////////////
// Update player coordinates based on key presses - key press == 5px change in position
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
	{
		pdx = cos(deg_to_rad(fix_ang(player->angle - 90)));
		pdy = sin(deg_to_rad(fix_ang(player->angle + 90)));
		if (no_wall(game, pdx * KEY_PRESS, pdy * KEY_PRESS))
		{
			player->coordinates.x += pdx * KEY_PRESS;
			player->coordinates.y += pdy * KEY_PRESS;
		}
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		pdx = cos(deg_to_rad(fix_ang(player->angle + 90)));
		pdy = sin(deg_to_rad(fix_ang(player->angle - 90)));
		if (no_wall(game, pdx * KEY_PRESS, pdy * KEY_PRESS))
		{
			player->coordinates.x += pdx * KEY_PRESS;
			player->coordinates.y += pdy * KEY_PRESS;
		}
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		if (no_wall(game, pdx * KEY_PRESS, -pdy * KEY_PRESS))
		{
			player->coordinates.x += pdx * KEY_PRESS;
			player->coordinates.y -= pdy * KEY_PRESS;
		}
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		if (no_wall(game, -pdx * KEY_PRESS, pdy * KEY_PRESS))
		{
			player->coordinates.x -= pdx * KEY_PRESS;
			player->coordinates.y += pdy * KEY_PRESS;
		}
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{

		player->angle += fix_ang(KEY_PRESS);
		player->angle = fix_ang(player->angle);
		pdx = cos(deg_to_rad(player->angle));
		pdy = sin(deg_to_rad(player->angle));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{

		player->angle -= fix_ang(KEY_PRESS);
		player->angle = fix_ang(player->angle);
		pdx = cos(deg_to_rad(player->angle));
		pdy = sin(deg_to_rad(player->angle));
	}
	printf("Player Angle: %f\n", player->angle);
////////////////////////////////////////////////////////
// Ray casting and Wall rendering
	draw_wall(game);
}


bool no_wall(game_t *game, double step_x, double step_y)
{
	player_t	*player;
	point_t		new_xy;
	point_t		map_xy;

	player = game->player;
	new_xy.x = player->coordinates.x + step_x;
	new_xy.y = player->coordinates.y + step_y;
	map_xy.x = (int)new_xy.x / SQUARE_SIZE;
	map_xy.y = (int)new_xy.y / SQUARE_SIZE;
	if (map_xy.x >= 0 && map_xy.x < game->map->width &&
		map_xy.y >= 0 && map_xy.y < game->map->height &&
		game->map->map[(int)map_xy.y][(int)map_xy.x] != M_WALL)
	{
		return true;
	} else
	{
		return false;
	}
}
