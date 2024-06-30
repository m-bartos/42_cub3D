/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_actions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:25:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 18:38:59 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	step_right(t_move_player *p)
{
	p->pdx = cos(deg_to_rad(fix_ang(p->player->angle - 90)));
	p->pdy = sin(deg_to_rad(fix_ang(p->player->angle + 90)));
	if (no_wall(p->game, p->pdx * KEY_PRESS, p->pdy * KEY_PRESS))
	{
		p->player->coordinates.x += p->pdx * KEY_PRESS;
		p->player->coordinates.y += p->pdy * KEY_PRESS;
	}
}

void	step_left(t_move_player *p)
{
	p->pdx = cos(deg_to_rad(fix_ang(p->player->angle + 90)));
	p->pdy = sin(deg_to_rad(fix_ang(p->player->angle - 90)));
	if (no_wall(p->game, p->pdx * KEY_PRESS, p->pdy * KEY_PRESS))
	{
		p->player->coordinates.x += p->pdx * KEY_PRESS;
		p->player->coordinates.y += p->pdy * KEY_PRESS;
	}
}

void	move_forward(t_move_player *p)
{
	if (no_wall(p->game, p->pdx * KEY_PRESS, -p->pdy * KEY_PRESS))
	{
		p->player->coordinates.x += p->pdx * KEY_PRESS;
		p->player->coordinates.y -= p->pdy * KEY_PRESS;
	}
}

void	move_backward(t_move_player *p)
{
	if (no_wall(p->game, -p->pdx * KEY_PRESS, p->pdy * KEY_PRESS))
	{
		p->player->coordinates.x -= p->pdx * KEY_PRESS;
		p->player->coordinates.y += p->pdy * KEY_PRESS;
	}
}
