/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:40:42 by orezek            #+#    #+#             */
/*   Updated: 2024/06/17 18:40:54 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <math.h>
# include "../cube.h"

int FixAng(int a)
{
	if(a > 359)
	{
		a -= 360;
	}
	if(a < 0)
	{
		a += 360;
	}
	return a;
}

// Convert degrees to radians
float degToRad(int a)
{
	return a*M_PI/180.0;
}
