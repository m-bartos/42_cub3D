/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map_borders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:25:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:28:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

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

char	**add_borders_fill_spaces(char **map_array)
{
	if (map_array == NULL)
		return (NULL);
	map_array = add_first_row(map_array);
	map_array = add_last_row(map_array);
	map_array = add_vertical_borders(map_array);
	fill_spaces(map_array);
	return (map_array);
}
