/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:08:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 15:52:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	set_map_size(t_map *map)
{
	map->width = max_line_width(map->map);
	map->height = ft_len_of_arr(map->map);
}

void	check_valid_map_chars(char **map)
{
	int		i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (!(map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W'
				|| ft_isspace(map[i][j])))
			{
				ft_putstr_fd("Error: Not valid chars in map or ", 2);
				ft_putstr_fd("map is not indented with new line.\n", 2);
				clean_map(NULL);
				exit(20);
			}
			j++;
		}
		i++;
	}
}

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (ft_isspace(line[i]) || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}
