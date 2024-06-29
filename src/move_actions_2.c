/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_actions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:26:42 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 18:27:19 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	turn_left(t_move_player *p)
{
	p->player->angle += fix_ang(KEY_PRESS);
	p->player->angle = fix_ang(p->player->angle);
	p->pdx = cos(deg_to_rad(p->player->angle));
	p->pdy = sin(deg_to_rad(p->player->angle));
}

void	turn_right(t_move_player *p)
{
	p->player->angle -= fix_ang(KEY_PRESS);
	p->player->angle = fix_ang(p->player->angle);
	p->pdx = cos(deg_to_rad(p->player->angle));
	p->pdy = sin(deg_to_rad(p->player->angle));
}
