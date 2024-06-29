/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:31:44 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 15:07:57 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

char	**get_file_array(int fd)
{
	char	**map_array;
	char	*one_line;
	char	*lines;
	char	*old_lines;

	old_lines = NULL;
	one_line = get_next_line(fd);
	if (one_line == NULL)
		return (NULL);
	lines = ft_strjoin("", one_line);
	free(one_line);
	while (1)
	{
		one_line = get_next_line(fd);
		if (one_line == NULL)
			break ;
		old_lines = lines;
		lines = ft_strjoin(old_lines, one_line);
		free(old_lines);
		free(one_line);
	}
	map_array = ft_split_empty(lines, '\n');
	free(lines);
	return (map_array);
}

char	**file_to_array(char *map_name)
{
	int		fd;
	char	**map_array;

	fd = open(map_name, O_RDONLY, 0444);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Config file not found. \n", 2);
		clean_map(NULL);
		exit(1);
	}
	else
		ft_putstr_fd("Config file found!\n", 1);
	map_array = get_file_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Config file empty\n", 2);
		clean_map(NULL);
		exit(2);
	}
	return (map_array);
}

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

void	map_flood_fill(char **map_array, size_t y, size_t x)
{
	if (map_array[y][x] == 'n' || map_array[y][x] == 's'
		|| map_array[y][x] == 'e' || map_array[y][x] == 'w'
		|| map_array[y][x] == '5' || map_array[y][x] == M_WALL)
		return ;
	if (map_array[y][x] == M_FLOOR)
		map_array[y][x] = '5';
	else if (map_array[y][x] == 'N')
		map_array[y][x] = 'n';
	else if (map_array[y][x] == 'S')
		map_array[y][x] = 's';
	else if (map_array[y][x] == 'E')
		map_array[y][x] = 'e';
	else if (map_array[y][x] == 'W')
		map_array[y][x] = 'w';
	else if (map_array[y][x] == M_OUT)
	{
		ft_putstr_fd("Map error: Open map.\n", 2);
		ft_free_array(map_array);
		clean_map(NULL);
		exit (1);
	}
	map_flood_fill(map_array, y + 1, x);
	map_flood_fill(map_array, y - 1, x);
	map_flood_fill(map_array, y, x + 1);
	map_flood_fill(map_array, y, x - 1);
}

char	**seperate_map(char **file_content)
{
	int		i;
	int		first_line;
	int		last_line;
	char	**map;

	last_line = ft_len_of_arr(file_content) - 1;
	while (last_line > 0)
	{
		if (!is_empty_line(file_content[last_line]))
			break ;
		last_line--;
	}
	first_line = last_line - 1;
	if (first_line < 0)
		first_line = 0;
	while (first_line > 0)
	{
		if (is_empty_line(file_content[first_line]))
			break ;
		first_line--;
	}
	first_line++;
	map = ft_init_array(last_line - first_line + 1);
	i = 0;
	while (first_line + i <= last_line)
	{
		map[i] = file_content[first_line + i];
		file_content[first_line + i] = NULL;
		i++;
	}
	return (map);
}

void	replace_start_pos_in_map(char **map)
{
	int		i;
	size_t	j;

	i = 0;
	while(map[i])
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

void	fill_map_struct(map_t *map, char *str)
{
	char	**map_flooded;

	check_suffix(str);
	ft_putstr_fd("---RUNNING_CONFIG_FILE_CHECK----\n", 1);
	map->temp_file_arr = file_to_array(str);
	map->map = seperate_map(map->temp_file_arr);
	get_textures(map, map->temp_file_arr);
	check_textures(map);
	get_colors(map, map->temp_file_arr);
	check_colors(map);
	ft_free_array(map->temp_file_arr);
	map->temp_file_arr = NULL;
	map->map = add_borders_fill_spaces(map->map);
	check_start_possitions(map->map);
	get_player_pos(map);
	map_flooded = ft_arrdup(map->map);
	map_flood_fill(map_flooded, map->player->coordinates.y, map->player->coordinates.x);
	ft_putstr_fd("---CONFIG_FILE_CHECK_OK----\n", 1);
	replace_start_pos_in_map(map->map);
	map->player->coordinates.x = map->player->coordinates.x * SQUARE_SIZE + SQUARE_SIZE / 2;
	map->player->coordinates.y = map->player->coordinates.y * SQUARE_SIZE + SQUARE_SIZE / 2;
	map->width = max_line_width(map->map);
	map->height = ft_len_of_arr(map->map);
}
