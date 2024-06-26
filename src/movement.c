/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/26 14:49:08 by orezek           ###   ########.fr       */
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
	set_img_background(game->game_planes->game_plane, R_BACKGROUND);
////////////////////////////////////////////////////////////////////////////////
// Update player coordinates based on key presses - key press == 5px change in position
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
	{
		if (no_wall(game, pdx * KEY_PRESS, pdy * KEY_PRESS))
		{
			player->coordinates.x += pdy * KEY_PRESS;
			player->coordinates.y += pdx * KEY_PRESS;
		}
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		if (no_wall(game, -pdx * KEY_PRESS, -pdy * KEY_PRESS))
		{
			player->coordinates.x -= pdy * KEY_PRESS;
			player->coordinates.y -= pdx * KEY_PRESS;
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
	printf("X%f: Y%f:\n", player->coordinates.x, player->coordinates.y);
	printf("Angle: %f\n", player->player_angle);
////////////////////////////////////////////////////////
// Ray casting and Wall rendering
	draw_wall(game);
}


bool no_wall(game_t *game, double step_x, double step_y)
{
    player_t *player;
    double new_x, new_y;
	int map_x;
	int map_y;

	player = &game->player;
    // Calculate the new position after the step and key W
    new_x = player->coordinates.x + step_x;
    new_y = player->coordinates.y + step_y;

    // Convert new position to map grid indices
    map_x = (int)new_x / SQUARE_SIZE;
    map_y = (int)new_y / SQUARE_SIZE;
	printf("MAP_X: %i, MAP_Y: %i\n", map_x, map_y);
    // Check if the new position is within the map boundaries and not a wall
    if (map_x >= 0 && map_x < game->game_map.width &&
        map_y >= 0 && map_y < game->game_map.height &&
        game->game_map.map[map_y][map_x] != M_WALL)
	{
        return true;
    } else
	{
        return false;
    }
}
