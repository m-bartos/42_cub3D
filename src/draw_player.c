/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:20:32 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 20:27:15 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_player(game_t *game)
{
	point_t	start;
	point_t	end;
	double	pdx;
	double	pdy;

	pdx = cos(deg_to_rad(game->player.player_angle));
	pdy = sin(deg_to_rad(game->player.player_angle));
	start.x = game->player.coordinates.x;
	start.y = game->player.coordinates.y;
	end.x = game->player.coordinates.x;
	end.y = game->player.coordinates.y;
	end.x = end.x + pdx * PLAYER_LENGTH;
	end.y = end.y - pdy * PLAYER_LENGTH;
	draw_line(game->game_planes->left_plane, start.x, start.y, end.x, end.y, PLAYER);
}
