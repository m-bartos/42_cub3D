/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:20:32 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:21:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_player(t_game *game)
{
	t_point	start;
	t_point	end;
	double	pdx;
	double	pdy;

	pdx = cos(deg_to_rad(game->player->angle));
	pdy = sin(deg_to_rad(game->player->angle));
	start.x = game->player->coordinates.x;
	start.y = game->player->coordinates.y;
	end.x = game->player->coordinates.x;
	end.y = game->player->coordinates.y;
	end.x = end.x + pdx * PLAYER_LENGTH;
	end.y = end.y - pdy * PLAYER_LENGTH;
	draw_line(game->planes->game_plane, start, end, PLAYER);
}
