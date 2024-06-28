/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:36:47 by orezek            #+#    #+#             */
/*   Updated: 2024/06/28 23:00:53 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	load_map(char *map_str, game_t *game)
{
	int		x = 0;
	int		y = 0;
	char	**game_map;
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
	game->game_map->map = game_map;
	game->game_map->width = x;
	game->game_map->height = y;
	return (1);
}

void	draw_map(mlx_image_t *image, game_t *game)
{
	char	**arr = game->game_map->map;
	int		s_size = game->game_map->square_size;
	int		y_map_size = game->game_map->height;
	int		x_map_size = game->game_map->width;
	int		x;
	int		y;

	y = 0;
	// draws y axes
	while (y < y_map_size)
	{
		x = 0;
		// draws x axes
		while (x < x_map_size)
		{
			if (arr[y][x] == M_WALL)
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, MINI_WALL);
			else if (arr[y][x] == M_FLOOR)
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, MINI_FLOOR);
			x++;
		}
		y++;
	}
}
