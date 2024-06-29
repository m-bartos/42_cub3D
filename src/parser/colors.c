/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	check_valid_color_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == ',')
			i++;
		else
		{
			ft_putstr_fd("Error: Not valid format of RGB color.\n", 2);
			clean_map(NULL);
			exit(99);
		}
	}
}

int get_color_from_str(char *str)
{
	char	**colors;
	int		red;
	int		green;
	int		blue;
	int		color;

	check_valid_color_line(&str[2]);
	colors = ft_split_e(&str[2], ',');
	if (ft_len_of_arr(colors) < 3)
	{
		ft_putstr_fd("Error: Not valid format of RGB color.\n" , 2);
		clean_map(NULL);
		ft_free_array(colors);
		exit(99);
	}
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	printf("R:%u, G:%u, B:%u\n", red, green, blue);
	if (red < 0 || green < 0 || blue < 0 ||
		red > 255 || green > 255 || blue > 255)
	{
		ft_putstr_fd("Error: Not valid format of RGB color.\n" , 2);
		clean_map(NULL);
		ft_free_array(colors);
		exit(99);
	}
	color = get_rgba(red, green, blue, 255);
	ft_free_array(colors);
	return (color);
}

void	get_colors(map_t *map, char **file_arr)
{
	int	i;

	if (file_arr == NULL)
		return ;
	i = 0;
	while(file_arr[i])
	{
		if (ft_strncmp(file_arr[i], "F ", 2) == 0)
			map->floor_color = get_color_from_str(file_arr[i]);
		else if (ft_strncmp(file_arr[i], "C ", 2) == 0)
			map->ceiling_color = get_color_from_str(file_arr[i]);
		i++;
	}
}

void	check_colors(map_t *map)
{
	if (map->ceiling_color == 0 || map->floor_color == 0)
	{
		ft_putstr_fd("Error: Not all colors provided.\n", 2);
		clean_map(NULL);
		exit(99);
	}
}
