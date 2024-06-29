/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:15:57 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 15:43:47 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	get_player_pos(map_t *map)
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
				map->player->coordinates.x = x;
				map->player->coordinates.y = y;
				if (map_array[y][x] == 'N')
					map->player->player_angle = NORTH_D;
				if (map_array[y][x] == 'S')
					map->player->player_angle = SOUTH_D;
				if (map_array[y][x] == 'E')
					map->player->player_angle = EAST_D;
				if (map_array[y][x] == 'W')
					map->player->player_angle = WEST_D;
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
}
