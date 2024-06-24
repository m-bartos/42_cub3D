/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:36:47 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 11:29:06 by orezek           ###   ########.fr       */
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
	game->game_map.map = game_map;
	game->game_map.width = x;
	game->game_map.height = y;
	return (1);
}

void	draw_map_char(mlx_image_t *image, game_t *game)
{
	char **arr = game->game_map.map;
	int s_size = 64;
	int y_map_size = 18;
	int x_map_size = 15;
	int y = 0;
	// draws y axes
	while (y < y_map_size)
	{
		int x = 0;
		// draws x axes
		while (x < x_map_size)
		{
			//printf("%d", arr[y][x]);
			if (arr[y][x] == '1')
			{
				//draw_square(image, x * s_size, y * s_size, w_color);
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, MINI_WALL);
			}
			else
				//draw_square(image, x * s_size, y * s_size, f_color);
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, MINI_FLOOR);
			x++;
		}
		//printf("\n");
		y++;
	}
}
