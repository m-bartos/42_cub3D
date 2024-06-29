/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:31:44 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:40:39 by mbartos          ###   ########.fr       */
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
	// ft_free_array(map_array); // test only
	// clean_map(NULL); // test only
	// exit(99); // test only
	return (map_array);
}

char	**file_to_array(char *map_name)
{
	int		fd;
	char	**map_array;
	// char	*map_path;

	// map_path = ft_strjoin("map/", map_name);
	// printf("Looking for map at: %s\n", map_path);
	fd = open(map_name, O_RDONLY, 0444);
	// free(map_path);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Map not found. It has to be in map folder.\n", 2); // change message
		clean_map(NULL);
		exit(1);
	}
	else
		ft_putstr_fd("Map found!\n", 1);
	map_array = get_file_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Map file empty\n", 2);
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
		clean_map(NULL); //free array and map_t
		exit (1);
	}
	map_flood_fill(map_array, y + 1, x);
	map_flood_fill(map_array, y - 1, x);
	map_flood_fill(map_array, y, x + 1);
	map_flood_fill(map_array, y, x - 1);
}

char	**seperate_map(char **file_content)
{
	int	i;
	int	first_line;
	int	last_line;
	char	**map;

	ft_putstr_fd("------FILE------\n", 1);
	ft_print_array(file_content);
	ft_putstr_fd("------FILE------\n\n", 1);
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
	ft_putstr_fd("---- MAP ----\n", 1);
	ft_print_array(map);
	ft_putstr_fd("---- MAP ----\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("---- file_content ----\n", 1);
	ft_print_array(file_content);
	ft_putstr_fd("---- file_content ----\n\n", 1);
	return(map);
}

char	*delete_extra_spaces(char *str)
{
	int		i;
	char	*first_part;
	char	*second_part;
	char	*old_str;

	if (str[0] == 0)
		return (str);
	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' && str[i - 1] == ' ')
		{
			old_str = str;
			first_part = ft_substr_e(str, 0, i);
			second_part = ft_substr_e(str, i + 1, ft_strlen(str));
			str = ft_strjoin_e(first_part, second_part);
			free(old_str);
			free(first_part);
			free(second_part);
			i--;
		}
		i++;
	}
	return (str);
}

void	replace_start_pos_in_map(char **map)
{
	int	i;
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

	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("-RUNNING_MAP_CHECK-\n", 1);
	ft_putstr_fd("-------------------\n", 1);

	check_suffix(str);

	map->temp_file_arr = file_to_array(str);
	map->map = seperate_map(map->temp_file_arr);

	get_textures(map, map->temp_file_arr);
	check_textures(map);
	get_colors(map, map->temp_file_arr);
	check_colors(map);
	ft_print_array(map->temp_file_arr);
	ft_free_array(map->temp_file_arr);
	map->temp_file_arr = NULL;

	// printf("NO:/%s/, SO:/%s/, EA:/%s/, WE:/%s/\n", map->textures->angle_90, map->textures->angle_270, map->textures->angle_0, map->textures->angle_180);
	// printf("Ceiling: %u, floor: %u\n", map->ceiling_color, map->floor_color);

	// map checker:
	// Error overwrites the map array with some old map
	ft_print_array(map->map);
	ft_putstr_fd("\n\n", 1);
	map->map = add_borders_fill_spaces(map->map);
	ft_print_array(map->map);
	ft_putstr_fd("\n\n", 1);

	check_start_possitions(map->map);
	// check only one start possition
	get_player_pos(map);
	map_flooded = ft_arrdup(map->map);
	ft_print_array(map_flooded);
	map_flood_fill(map_flooded, map->player->coordinates.y, map->player->coordinates.x);

	printf("-----FLOODED MAP-----\n"); //printing
	ft_print_array(map_flooded); //printing
	printf("-----FLOODED MAP-----\n\n");
	ft_free_array(map_flooded);

	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("---MAP_CHECK_OK----\n", 1);
	ft_putstr_fd("-------------------\n\n", 1);

	replace_start_pos_in_map(map->map);
	map->player->coordinates.x = map->player->coordinates.x * SQUARE_SIZE + SQUARE_SIZE / 2;
	map->player->coordinates.y = map->player->coordinates.y * SQUARE_SIZE + SQUARE_SIZE / 2;
	map->width = max_line_width(map->map);
	map->height = ft_len_of_arr(map->map);
	// printf("W:%d, H:%d\n", map->width, map->height);
	// printf("Player angle:%f\n", map->player->player_angle);
}

