/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:31:44 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 12:55:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

char	**load_file_to_array(int fd)
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

char	**get_file_array(char *map_name)
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
	map_array = load_file_to_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Config file empty\n", 2);
		clean_map(NULL);
		exit(2);
	}
	return (map_array);
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
	first_line = last_line - 1;
	if (first_line < 0)
		first_line = 0;
	while (first_line >= 0 && !is_empty_line(file_content[first_line]))
		first_line--;
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

void	fill_map_struct(map_t *map, char *str)
{
	player_t	*player;

	player = map->player;
	check_suffix(str);
	ft_putstr_fd("---- RUNNING CONFIG_FILE CHECK ----\n", 1);
	map->temp_arr = get_file_array(str);
	delete_last_empty_lines_in_arr(map->temp_arr);
	map->map = seperate_map(map->temp_arr);
	check_valid_map_chars(map->map);
	get_textures(map, map->temp_arr);
	check_textures(map);
	get_colors(map, map->temp_arr);
	check_colors(map);
	ft_free_array(map->temp_arr);
	map->temp_arr = NULL;
	map->map = add_borders_fill_spaces(map->map);
	check_start_possitions(map->map);
	get_player_pos(map);
	map->temp_arr = ft_arrdup(map->map);
	map_flood_fill(map->temp_arr, player->coordinates.y, player->coordinates.x);
	ft_free_array(map->temp_arr);
	map->temp_arr = NULL;
	replace_start_pos_in_map(map->map);
	ft_putstr_fd("---- CONFIG_FILE CHECK DONE - OK ----\n", 1);
	set_map_size(map);
}
