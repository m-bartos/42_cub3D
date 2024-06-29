/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:39:12 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 17:02:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"


uint32_t get_pixel_color(mlx_texture_t *texture, int y_height, int x_width)
{
	uint32_t	i;
	uint32_t	color;

	i = (y_height * texture->width + x_width) * texture->bytes_per_pixel;
	color = get_rgba(texture->pixels[i], texture->pixels[i+1],texture->pixels[i+2], texture->pixels[i+3]);
	return color;
}

mlx_texture_t	*get_texture(game_t *game, double h_distance, double v_distance)
{
	double	ra;

	ra = game->player->angle;
	if (h_distance < v_distance)
	{
		if (deg_to_rad(ra) > deg_to_rad(NORTH_D) && deg_to_rad(ra) < deg_to_rad(SOUTH_D))
			return (game->map->txts->angle_90);
		else
			return (game->map->txts->angle_270);
	}
	else
	{
		if ((deg_to_rad(ra) > deg_to_rad(WEST_D) && deg_to_rad(ra) < deg_to_rad(EAST_D)))
			return(game->map->txts->angle_180);
		else
			return (game->map->txts->angle_0);
	}
	return (NULL);

}
