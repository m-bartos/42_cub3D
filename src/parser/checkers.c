/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:34:44 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:43:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	check_start_possitions(char **map_array)
{
	int	num_of_nsew;
	int	i;
	int	j;

	i = 0;
	num_of_nsew = 0;
	while (map_array[i])
	{
		j = 0;
		while (j < (int) ft_strlen(map_array[i]))
		{
			if (map_array[i][j] == 'N' || map_array[i][j] == 'S'
				|| map_array[i][j] == 'E' || map_array[i][j] == 'W')
				num_of_nsew += 1;
			j++;
		}
		i++;
	}
	if (num_of_nsew != 1)
	{
		ft_putstr_fd("Map error: More starts (NSEW).\n", 2);
		clean_map(NULL);
		exit(1);
	}
}

void	check_suffix(char *str)
{
	char	*suf;
	size_t	str_len;
	size_t	suf_len;

	suf = ft_strdup(".cub");
	str_len = ft_strlen(str);
	suf_len = ft_strlen(suf);
	if (ft_strncmp(&str[str_len - suf_len], suf, suf_len + 1) != 0)
	{
		ft_putstr_fd("Error: invalid map name, *.cub suffix missing\n", 2);
		free(suf);
		clean_map(NULL);
		exit(1);
	}
	free(suf);
}
