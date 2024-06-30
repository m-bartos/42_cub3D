/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:09 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 14:21:06 by orezek           ###   ########.fr       */
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

void	get_textures(t_map *map, char **file_arr)
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
		if (ft_strncmp(file_arr[i], "NO ", 3) == 0 && !map->txts->angle_0)
			map->txts->angle_0 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "SO ", 3) == 0 && !map->txts->angle_180)
			map->txts->angle_180 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "EA ", 3) == 0 && !map->txts->angle_270)
			map->txts->angle_270 = load_png_from_path(&file_arr[i][3]);
		else if (ft_strncmp(file_arr[i], "WE ", 3) == 0 && !map->txts->angle_90)
			map->txts->angle_90 = load_png_from_path(&file_arr[i][3]);
		i++;
	}
}

void	check_textures(t_map *map)
{
	if (map->txts->angle_0 == NULL
		|| map->txts->angle_90 == NULL
		|| map->txts->angle_180 == NULL
		|| map->txts->angle_270 == NULL)
	{
		ft_putstr_fd("Error: Not all textures provided.\n", 2);
		clean_map(NULL);
		exit(99);
	}
	else
		ft_putstr_fd("Textures found and imported!\n", 1);
}
