/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:59 by orezek            #+#    #+#             */
/*   Updated: 2024/06/28 22:58:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


double	get_point_distance(game_t *game, point_t *coordinates)
{
	double				distance;
	player_t	*pl;

	pl = game->player;
	distance = sqrt((coordinates->x - pl->coordinates.x) * (coordinates->x - pl->coordinates.x) + (coordinates->y - pl->coordinates.y) * (coordinates->y - pl->coordinates.y));
	return (distance);
}
