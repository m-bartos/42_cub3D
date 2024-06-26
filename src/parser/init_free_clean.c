/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:19:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 15:58:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	init_map(t_map *map)
{
	map->ceiling_color = 0;
	map->floor_color = 0;
	map->height = 0;
	map->width = 0;
	map->temp_arr = NULL;
	map->map = NULL;
	map->player = malloc(sizeof(t_player));
	if (map->player == NULL)
		exit(2);
	map->player->fov = 60.0;
	map->player->coordinates.x = 0;
	map->player->coordinates.y = 0;
	map->player->angle = 0;
	map->txts = malloc(sizeof(t_textures));
	if (map->txts == NULL)
		exit(2);
	map->txts->angle_0 = NULL;
	map->txts->angle_90 = NULL;
	map->txts->angle_180 = NULL;
	map->txts->angle_270 = NULL;
	map->square_size = SQUARE_SIZE;
	clean_map(map);
}

void	free_map(t_map *map)
{
	ft_free_array(map->map);
	ft_free_array(map->temp_arr);
	free(map->player);
	if (map->txts->angle_0)
		mlx_delete_texture(map->txts->angle_0);
	if (map->txts->angle_90)
		mlx_delete_texture(map->txts->angle_90);
	if (map->txts->angle_180)
		mlx_delete_texture(map->txts->angle_180);
	if (map->txts->angle_270)
		mlx_delete_texture(map->txts->angle_270);
	free(map->txts);
}

void	clean_map(t_map *map)
{
	static t_map	*static_map;

	if (map != NULL)
	{
		static_map = map;
		return ;
	}
	free_map(static_map);
}
