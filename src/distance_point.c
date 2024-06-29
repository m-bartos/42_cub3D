/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:59 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 11:40:13 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	get_point_distance(game_t *game, point_t *coordinates)
{
	double		distance;
	player_t	*pl;

	pl = game->player;
	distance = sqrt((coordinates->x - pl->coordinates.x)
			* (coordinates->x - pl->coordinates.x)
			+ (coordinates->y - pl->coordinates.y)
			* (coordinates->y - pl->coordinates.y));
	return (distance);
}
