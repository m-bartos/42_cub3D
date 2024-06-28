/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:39:12 by orezek            #+#    #+#             */
/*   Updated: 2024/06/28 12:54:58 by orezek           ###   ########.fr       */
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

	ra = game->player.player_angle;
	if (h_distance < v_distance)
	{
		if (deg_to_rad(ra) > deg_to_rad(NORTH_D) && deg_to_rad(ra) < deg_to_rad(SOUTH_D))
			return (game->game_map.game_textures.ea);
		else
			return (game->game_map.game_textures.we);
	}
	else
	{
		if ((deg_to_rad(ra) > deg_to_rad(EAST_D) && deg_to_rad(ra) < deg_to_rad(WEST_D)))
			return(game->game_map.game_textures.so);
		else
			return (game->game_map.game_textures.no);
	}
	return (NULL);

}
