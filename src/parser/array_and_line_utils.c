/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_and_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:33:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/30 12:48:46 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
		{
			return (0);
		}
	}
	return (1);
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
		if ((ft_isspace(str[i])) && (ft_isspace(str[i - 1])))
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

void	delete_last_empty_lines_in_arr(char **file_content)
{
	int		last_line;

	last_line = ft_len_of_arr(file_content) - 1;
	while (last_line > 0)
	{
		if (!is_empty_line(file_content[last_line]))
			break ;
		free(file_content[last_line]);
		file_content[last_line] = NULL;
		last_line--;
	}
}
