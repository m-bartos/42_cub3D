/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:02:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/28 15:30:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	map->textures = malloc(sizeof(textures_t));
	if (map->textures == NULL)
		exit(2);
	map->textures->t_angle_0 = NULL;
	map->textures->t_angle_90 = NULL;
	map->textures->t_angle_180 = NULL;
	map->textures->t_angle_270 = NULL;
	map->square_size = 64;
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
	// free(map);
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

int main (int argc, char **argv)
{
	map_t 		map;

	error_argc(argc);
	init_map(&map);
	fill_map_struct(&map, argv[1]);
	clean_map(NULL);
	return (0);
}


// int	main ()
// {
// 	char **array;

// 	array = ft_split_empty("\nah\n\n\naha\na\n\n \n ", '\n');
// 	// array = ft_split("ahaha", '\n');
// 	ft_print_array(array);
// 	ft_free_array(array);
// }