/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:50:59 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 15:53:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double	get_point_distance(t_game *game, t_point *coordinates)
{
	double		distance;
	t_player	*pl;

	pl = game->player;
	distance = sqrt((coordinates->x - pl->coordinates.x)
			* (coordinates->x - pl->coordinates.x)
			+ (coordinates->y - pl->coordinates.y)
			* (coordinates->y - pl->coordinates.y));
	return (distance);
}
