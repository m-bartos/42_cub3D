/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:15:57 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 15:53:08 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	set_player_coordinates_and_angle(t_map *map, size_t x, size_t y)
{
	char	**map_array;

	map_array = map->map;
	map->player->coordinates.x = x;
	map->player->coordinates.y = y;
	if (map_array[y][x] == 'N')
		map->player->angle = NORTH_D;
	if (map_array[y][x] == 'S')
		map->player->angle = SOUTH_D;
	if (map_array[y][x] == 'E')
		map->player->angle = EAST_D;
	if (map_array[y][x] == 'W')
		map->player->angle = WEST_D;
}

void	get_player_pos(t_map *map)
{
	char	**map_array;
	size_t	y;
	size_t	x;

	map_array = map->map;
	y = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			if (map_array[y][x] == 'N' || map_array[y][x] == 'S'
				|| map_array[y][x] == 'E' || map_array[y][x] == 'W')
			{
				set_player_coordinates_and_angle(map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	replace_start_pos_in_map(char **map)
{
	int		i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'E')
				map[i][j] = '0';
			if (map[i][j] == 'W')
				map[i][j] = '0';
			if (map[i][j] == 'S')
				map[i][j] = '0';
			if (map[i][j] == 'N')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
	ft_putstr_fd("Map found and OK!\n", 1);
}

void	change_player_coordinates_format(t_player *player)
{
	player->coordinates.x = SQUARE_SIZE * (player->coordinates.x + 0.5);
	player->coordinates.y = SQUARE_SIZE * (player->coordinates.y + 0.5);
}
