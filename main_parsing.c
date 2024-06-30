/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:02:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 14:21:06 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// void	init_map(t_map *map)
// {
// 	map->ceiling_color = 0;
// 	map->floor_color = 0;
// 	map->height = 0;
// 	map->width = 0;
// 	map->temp_file_arr = NULL;
// 	map->map = NULL;
// 	map->player = malloc(sizeof(t_player));
// 	if (map->player == NULL)
// 		exit(2);
// 	map->textures = malloc(sizeof(t_textures));
// 	if (map->textures == NULL)
// 		exit(2);
// 	map->textures->angle_0 = NULL;
// 	map->textures->angle_90 = NULL;
// 	map->textures->angle_180 = NULL;
// 	map->textures->angle_270 = NULL;
// 	map->square_size = 64;
// 	clean_map(map);
// }

// void	free_map(t_map *map)
// {
// 	ft_free_array(map->map);
// 	ft_free_array(map->temp_file_arr);
// 	free(map->player);
// 	if (map->textures->angle_0)
// 		mlx_delete_texture(map->textures->angle_0);
// 	if (map->textures->angle_90)
// 	mlx_delete_texture(map->textures->angle_90);
// 	if (map->textures->angle_180)
// 		mlx_delete_texture(map->textures->angle_180);
// 	if (map->textures->angle_270)
// 		mlx_delete_texture(map->textures->angle_270);
// 	free(map->textures);
// 	// free(map);
// }

// void	clean_map(t_map *map)
// {
// 	static t_map	*static_map;

// 	if (map != NULL)
// 	{
// 		static_map = map;
// 		return ;
// 	}
// 	free_map(static_map);
// }

// int main (int argc, char **argv)
// {
// 	t_map 		map;

// 	error_argc(argc);
// 	init_map(&map);
// 	fill_map_struct(&map, argv[1]);
// 	clean_map(NULL);
// 	return (0);
// }


// int	main ()
// {
// 	char **array;

// 	array = ft_split_empty("\nah\n\n\naha\na\n\n \n ", '\n');
// 	// array = ft_split("ahaha", '\n');
// 	ft_print_array(array);
// 	ft_free_array(array);
// }
