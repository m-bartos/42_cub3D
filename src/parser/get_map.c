/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:31:44 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/27 21:06:29 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	check_suffix(char *str)
{
	char	*suf;
	size_t	str_len;
	size_t	suf_len;
	size_t	i;

	suf = ft_strdup(".cub");
	str_len = ft_strlen(str);
	suf_len = ft_strlen(suf);
	i = 0;
	while (suf_len > 0)
	{
		if (str[str_len - suf_len] == suf[i])
		{
			suf_len--;
			i++;
		}
		else
		{
			ft_putstr_fd("Error: invalid map name, *.ber suffix missing\n", 2);
			free(suf);
			exit (1);
		}
	}
	free(suf);
}

int	max_line_width(char **map_array)
{
	int	max_length;
	int	i;

	if (map_array == NULL)
		return (0);
	max_length = 0;
	i = 0;
	while (map_array[i])
	{
		if ((int) ft_strlen(map_array[i]) > max_length)
			max_length = ft_strlen(map_array[i]);
		i++;
	}
	return (max_length);
}

char	**add_first_row(char **map_array)
{
	int		longest_line;
	int		i;
	char	*first_line;
	char	**old_map_array;

	longest_line = max_line_width(map_array);
	first_line = (char *) malloc(sizeof(char) * (longest_line + 1));
	if (first_line == NULL)
		exit(1);
	first_line[longest_line] = 0;
	ft_memset(first_line, M_OUT, longest_line);
	old_map_array = map_array;
	map_array = ft_init_array(ft_len_of_arr(map_array) + 1);
	map_array[0] = first_line;
	i = 0;
	while (old_map_array[i])
	{
		map_array[i + 1] = old_map_array[i];
		i++;
	}
	free(old_map_array);
	return (map_array);
}

char	**add_last_row(char **map_array)
{
	int		longest_line;
	int		i;
	char	*last_line;
	char	**old_map_array;

	longest_line = max_line_width(map_array);
	last_line = (char *) malloc(sizeof(char) * (longest_line + 1));
	if (last_line == NULL)
		exit(1);
	last_line[longest_line] = 0;
	ft_memset(last_line, M_OUT, longest_line);
	old_map_array = map_array;
	map_array = ft_init_array(ft_len_of_arr(map_array) + 1);
	i = 0;
	while (old_map_array[i])
	{
		map_array[i] = old_map_array[i];
		i++;
	}
	map_array[i] = last_line;
	free(old_map_array);
	return (map_array);
}

char	**add_vertical_borders(char **map_array)
{
	char	*old_line;
	int		i;

	i = 0;
	while (map_array[i])
	{
		old_line = map_array[i];
		map_array[i] = ft_strjoin_e(old_line, "9");
		free(old_line);
		old_line = map_array[i];
		map_array[i] = ft_strjoin_e("9", old_line);
		free(old_line);

		i++;
	}
	return (map_array);
}

char	**add_borders(char **map_array)
{
	if (map_array == NULL)
		return (NULL);
	map_array = add_first_row(map_array);
	map_array = add_last_row(map_array);
	map_array = add_vertical_borders(map_array);
	return (map_array);
}

void	fill_spaces(char **map_array)
{
	int	i;
	int	j;

	if (map_array == NULL)
		return ;
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] == ' ')
				map_array[i][j] = '9';
			j++;
		}
		i++;
	}
}

char	**map_to_array(int fd)
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

char	**map_file_to_array(char *map_name, map_t *map)
{
	int		fd;
	// char	*map_path;
	char	**map_array;

	// map_path = ft_strjoin("map/", map_name);
	// printf("Looking for map at: %s\n", map_path);
	fd = open(map_name, O_RDONLY, 0444);
	// free(map_path);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Map not found. It has to be in map folder.\n", 2);
		free(map);
		exit(1);
	}
	else
		ft_putstr_fd("Map found!\n", 1);
	map_array = map_to_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Map file empty\n", 2);
		free(map);
		exit(2);
	}
	return (map_array);
}

char	**ft_arrdup(char **arr)
{
	size_t	i;
	char	**new_arr;

	new_arr = (char **) malloc((ft_len_of_arr(arr) + 1) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	get_player_pos(char **map_array, map_t *map)
{
	size_t	y;
	size_t	x;

	map->player->coordinates.x = 0;
	map->player->coordinates.y = 0;
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
		ft_putstr_fd("Map error: ", 2);
		ft_free_array(map_array);
		//free array and map_t
		exit (1);
	}
	map_flood_fill(map_array, y + 1, x);
	map_flood_fill(map_array, y - 1, x);
	map_flood_fill(map_array, y, x + 1);
	map_flood_fill(map_array, y, x - 1);
}

void	check_start_possitions(char **map_array)
{
	int	num_of_NSEW;
	int	i;
	int	j;

	i = 0;
	num_of_NSEW = 0;
	while (map_array[i])
	{
		j = 0;
		while(j < (int) ft_strlen(map_array[i]))
		{
			if (map_array[i][j] == 'N' || map_array[i][j] == 'S'
				|| map_array[i][j] == 'E' || map_array[i][j] == 'W')
				num_of_NSEW += 1;
			j++;
		}
		i++;
	}
	if (num_of_NSEW != 1)
	{
		ft_putstr_fd("Map error: ", 2);
		//map error
		ft_free_array(map_array);
		//free array and map_t
		exit(1);
	}
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
		{
			return (0);
		}
	}
	return (1);
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

	if (str[0] == 0)
		return (str);
	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' && str[i - 1] == ' ')
		{
			first_part = ft_substr_e(str, 0, i);
			second_part = ft_substr_e(str, i + 1, ft_strlen(str));
			str = ft_strjoin_e(first_part, second_part);
			free(first_part);
			free(second_part);
			i--;
		}
		i++;
	}
	return (str);
}

void	get_textures(map_t *map, char **file_content)
{
	int	i;

	map->ceiling_color = 123;
	if (file_content == NULL)
		return ;
	i = 0;
	while(file_content[i])
	{
		file_content[i] = ft_strtrim_e(file_content[i], " ");
		printf("%s\n", file_content[i]);
		file_content[i] = delete_extra_spaces(file_content[i]);
		printf("%s\n", file_content[i]);
		if (ft_strncmp(file_content[i], "NO ", 3) == 0)
			map->textures->angle_90 = ft_strdup_e(&file_content[i][3]);
		else if (ft_strncmp(file_content[i], "SO ", 3) == 0)
			map->textures->angle_270 = ft_strdup_e(&file_content[i][3]);
		else if (ft_strncmp(file_content[i], "WE ", 3) == 0)
			map->textures->angle_180 = ft_strdup_e(&file_content[i][3]);
		else if (ft_strncmp(file_content[i], "EA ", 3) == 0)
			map->textures->angle_0 = ft_strdup_e(&file_content[i][3]);
		i++;
	}
}

void	get_map(map_t *map, char *str)
{
	char	**map_flooded;
	char	**file_content;

	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("-RUNNING_MAP_CHECK-\n", 1);
	ft_putstr_fd("-------------------\n", 1);
	
	check_suffix(str);
	
	file_content = map_file_to_array(str, map);
	// map->map = map_file_to_array(str, map);
	map->map = seperate_map(file_content);

	get_textures(map, file_content);
	printf("NO:/%s/, SO:/%s/, EA:/%s/, WE:/%s/\n", map->textures->angle_90, map->textures->angle_270, map->textures->angle_0, map->textures->angle_180);
	map->map = add_borders(map->map);
	fill_spaces(map->map);
	check_start_possitions(map->map);
	//check only one start possition
	get_player_pos(map->map, map);
	map_flooded = ft_arrdup(map->map);
	map_flood_fill(map_flooded, map->player->coordinates.y, map->player->coordinates.x);
	
	printf("-----FLOODED MAP-----\n"); //printing
	ft_print_array(map_flooded); //printing
	printf("-----FLOODED MAP-----\n\n");
	
	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("---MAP_CHECK_OK----\n", 1);
	ft_putstr_fd("-------------------\n\n", 1);
	
	map->height = max_line_width(map->map) - 2;
	map->width = ft_len_of_arr(map->map);
	
	// ft_free_array(map->map);
	// ft_free_array(file_content);
	ft_free_array(map_flooded);
	
	// return (map);
}