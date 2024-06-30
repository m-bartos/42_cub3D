/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:36:47 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:21:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	load_map(char *map_str, t_game *game)
{
	int		x;
	int		y;
	char	**game_map;

	x = 0;
	y = 0;
	game_map = ft_split(map_str, '\n');
	if (!game_map)
		return (0);
	while (game_map[y])
	{
		x = 0;
		while (game_map[y][x])
			x++;
		y++;
	}
	game->map->map = game_map;
	game->map->width = x;
	game->map->height = y;
	return (1);
}

void	draw_map(mlx_image_t *image, t_game *game)
{
	t_draw_map	d;

	d = (t_draw_map){0};
	d.arr = game->map->map;
	d.s_size = game->map->square_size;
	d.y_map_size = game->map->height;
	d.x_map_size = game->map->width;
	while (d.y < d.y_map_size)
	{
		d.x = 0;
		while (d.x < d.x_map_size)
		{
			if (d.arr[d.y][d.x] == M_WALL)
				put_square(image, (t_point){.x = d.x * d.s_size,
					.y = d.y * d.s_size}, d.s_size, MINI_WALL);
			else if (d.arr[d.y][d.x] == M_FLOOR)
				put_square(image, (t_point){.x = d.x * d.s_size,
					.y = d.y * d.s_size}, d.s_size, MINI_FLOOR);
			d.x++;
		}
		d.y++;
	}
}
