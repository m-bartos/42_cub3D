/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:19:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:29:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	init_map(map_t *map)
{
	map->ceiling_color = 0;
	map->floor_color = 0;
	map->height = 0;
	map->width = 0;
	map->temp_file_arr = NULL;
	map->map = NULL;
	map->player = malloc(sizeof(player_t));
	if (map->player == NULL)
		exit(2);
	map->player->fov = 60.0;
	map->player->coordinates.x = 0;
	map->player->coordinates.y = 0;
	map->player->player_angle = 0;
	map->textures = malloc(sizeof(textures_t));
	if (map->textures == NULL)
		exit(2);
	map->textures->t_angle_0 = NULL;
	map->textures->t_angle_90 = NULL;
	map->textures->t_angle_180 = NULL;
	map->textures->t_angle_270 = NULL;
	map->square_size = SQUARE_SIZE;
	clean_map(map);
}

void	free_map(map_t *map)
{
	ft_free_array(map->map);
	ft_free_array(map->temp_file_arr);
	free(map->player);
	if (map->textures->t_angle_0)
		mlx_delete_texture(map->textures->t_angle_0);
	if (map->textures->t_angle_90)
		mlx_delete_texture(map->textures->t_angle_90);
	if (map->textures->t_angle_180)
		mlx_delete_texture(map->textures->t_angle_180);
	if (map->textures->t_angle_270)
		mlx_delete_texture(map->textures->t_angle_270);
	free(map->textures);
}

void	clean_map(map_t *map)
{
	static map_t	*static_map;

	if (map != NULL)
	{
		static_map = map;
		return ;
	}
	free_map(static_map);
}
