/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:28:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/06/29 14:59:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	error_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Expecting 2 args.\n", 2);
		ft_putstr_fd("Format: ./cub3D Map_file.cub\n", 1);
		exit(1);
	}
}
