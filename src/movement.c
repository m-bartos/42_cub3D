/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 18:24:26 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	init_move_player(t_move_player *p, void *param)
{
	*p = (t_move_player){0};
	p->game = (t_game *)param;
	p->player = p->game->player;
	p->pdx = cos(deg_to_rad(p->player->angle));
	p->pdy = sin(deg_to_rad(p->player->angle));
	if (PRT_CONSOLE)
		printf("Player Angle: %f\n", p->game->player->angle);
}

static void	clean_init_or_prev_screen(t_move_player *p)
{
	set_img_background(p->game->planes->game_plane, R_BACKGROUND);
}

bool	no_wall(t_game *game, double step_x, double step_y)
{
	t_player	*player;
	t_point		new_xy;
	t_point		map_xy;

	player = game->player;
	new_xy.x = player->coordinates.x + step_x;
	new_xy.y = player->coordinates.y + step_y;
	map_xy.x = (int)new_xy.x / SQUARE_SIZE;
	map_xy.y = (int)new_xy.y / SQUARE_SIZE;
	if (map_xy.x >= 0 && map_xy.x < game->map->width
		&& map_xy.y >= 0 && map_xy.y < game->map->height
		&& game->map->map[(int)map_xy.y][(int)map_xy.x] != M_WALL
		&& game->map->map[(int)map_xy.y][(int)map_xy.x] != M_OUT)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	move_player(mlx_key_data_t key, void *param)
{
	t_move_player	p;

	init_move_player(&p, param);
	clean_init_or_prev_screen(&p);
	if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_D)
		step_right(&p);
	else if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_A)
		step_left(&p);
	else if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_W)
		move_forward(&p);
	else if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_S)
		move_backward(&p);
	else if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_LEFT)
		turn_left(&p);
	else if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_RIGHT)
		turn_right(&p);
	else if (key.action == MLX_PRESS && key.key == MLX_KEY_ESCAPE)
		pres_esc(&p);
	draw_wall(p.game);
}
