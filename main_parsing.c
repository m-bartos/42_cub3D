/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:02:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/25 14:41:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_map(map_t *map)
{
	map->ceiling_color = 0;
	map->floor_color = 0;
	map->height = 0;
	map->width = 0;
	map->map = NULL;
	map->player = malloc(sizeof(player_t));
	if (map->player == NULL)
		exit(2);
	map->square_size = 64;
	
}

int main (int argc, char **argv)
{
	map_t 		map;
	
	// map = malloc(sizeof(map_t));
	// chceck fail malloc;
	error_argc(argc);
	init_map(&map);
	get_map(&map, argv[1]);
	return (0);
}