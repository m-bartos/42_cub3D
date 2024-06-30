/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:09 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 12:32:18 by mbartos          ###   ########.fr       */
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

void	get_textures(map_t *map, char **file)
{
	int		i;
	char	*temp_line;

	if (file == NULL)
		return ;
	i = 0;
	while (file[i])
	{
		temp_line = file[i];
		file[i] = ft_strtrim_e(file[i], " \t\n\r\v\f");
		free(temp_line);
		file[i] = delete_extra_spaces(file[i]);
		if (ft_strncmp(file[i], "NO ", 3) == 0 && !map->txts->angle_0)
			map->txts->angle_0 = load_png_from_path(&file[i][3]);
		else if (ft_strncmp(file[i], "SO ", 3) == 0 && !map->txts->angle_180)
			map->txts->angle_180 = load_png_from_path(&file[i][3]);
		else if (ft_strncmp(file[i], "EA ", 3) == 0 && !map->txts->angle_270)
			map->txts->angle_270 = load_png_from_path(&file[i][3]);
		else if (ft_strncmp(file[i], "WE ", 3) == 0 && !map->txts->angle_90)
			map->txts->angle_90 = load_png_from_path(&file[i][3]);
		i++;
	}
}

void	check_textures(map_t *map)
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
