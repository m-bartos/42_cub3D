/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:59 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 13:32:56 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


double	get_point_distance(game_t *game, point_t *coordinates)
{
	double				distance;
	player_t	pl;

	pl = game->player;
	distance = sqrt((coordinates->x - pl.coordinates.x) * (coordinates->x - pl.coordinates.x) + (coordinates->y - pl.coordinates.y) * (coordinates->y - pl.coordinates.y));
	return (distance);
}
