/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:09 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 15:01:57 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

mlx_texture_t	*load_png_from_path(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (texture == NULL)
	{
		ft_putstr_fd("Error: Problem with textures.\n", 2);
		clean_map(NULL);
		exit(88);
	}
	return (texture);
}

void	get_textures(map_t *map, char **file_arr)
{
	int		i;
	char	*temp_line;

	if (file_arr == NULL)
		return ;
	i = 0;
	while (file_arr[i])
	{
		temp_line = file_arr[i];
		file_arr[i] = ft_strtrim_e(file_arr[i], " ");
		free(temp_line);
		file_arr[i] = delete_extra_spaces(file_arr[i]);
		if (ft_strncmp(file_arr[i], "NO ", 3) == 0 && !map->textures->t_angle_0)
			map->textures->t_angle_0 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "SO ", 3) == 0 && !map->textures->t_angle_180)
			map->textures->t_angle_180 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "EA ", 3) == 0 && !map->textures->t_angle_270)
			map->textures->t_angle_270 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "WE ", 3) == 0 && !map->textures->t_angle_90)
			map->textures->t_angle_90 = load_png_from_path(&file_arr[i][3]);
		i++;
	}
}

void	check_textures(map_t *map)
{
	if (map->textures->t_angle_0 == NULL
		|| map->textures->t_angle_90 == NULL
		|| map->textures->t_angle_180 == NULL
		|| map->textures->t_angle_270 == NULL)
	{
		ft_putstr_fd("Error: Not all textures provided.\n", 2);
		clean_map(NULL);
		exit(99);
	}
}
