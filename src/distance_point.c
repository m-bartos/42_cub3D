/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:59 by orezek            #+#    #+#             */
/*   Updated: 2024/06/23 15:03:52 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


double	get_point_distance(game_t *game, point_t *coordinates)
{
	double				distance;
	player_location_t	pl;

	pl = game->init_player_location;
	distance = sqrt((coordinates->x - pl.player_coordinates.x) * (coordinates->x - pl.player_coordinates.x) + (coordinates->y - pl.player_coordinates.y) * (coordinates->y - pl.player_coordinates.y));
	return (distance);
}
