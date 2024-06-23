/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/23 18:13:40 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

void	draw_wall(game_t *game)
{
		point_t 	*hrc;
		point_t 	*vrc;
		double		corrected_distance;
		double		h_distance;
		double		v_distance;
		double		fov;
		double		pa;
		planes_t	*game_planes;

		pa = game->player.player_angle;
		game_planes =  game->game_planes;
		int f_color = get_rgba(255, 0, 0, 255);
		int c_color = get_rgba(0, 0, 255, 255);
		unsigned int color = get_rgba(0, 255, 0, 255);
		fov = 60;
		for (int r = 0; r < fov; r++)
		{
			hrc = get_horizontal_ray_coordinates_v1(game);
			vrc = get_vertical_ray_coordinates_v1(game);
			h_distance = get_point_distance(game, hrc);
			v_distance = get_point_distance(game, vrc);
			if (v_distance < h_distance)
				corrected_distance = v_distance * cos(deg_to_rad(fov - pa));
			else
				corrected_distance = h_distance * cos(deg_to_rad(fov - pa));

			int screen_height = game->game_planes->right_plane->height;
			int screen_width = game->game_planes->right_plane->width;
			int max_wall_height = screen_height; // Wall extends the whole vertical line when directly facing

			// Calculate the wall height based on the distance
			// Adjust the wall size multiplyer to something appropriate like 64 or 128
			int line_height = (128 * max_wall_height) / corrected_distance;
			if (line_height > screen_height)
				line_height = screen_height; // Ensure it doesn't exceed the screen height

			int line_offset = (screen_height / 2) - (line_height / 2); // Centering the wall slice vertically

			// Correct horizontal position for each ray
			int ray_x_position = (screen_width - 1) - r * (screen_width / fov); // Inverted to draw from left to right

			// Draw the wall slice by filling pixels vertically
			// for (int y = line_offset; y < line_offset + line_height; y++)
			//{
			// 	mlx_put_pixel(game_planes->right_plane, ray_x_position, y, color);  // Draw at the correct x-coordinate
			// }
			// floor

			draw_line(game_planes->right_plane, ray_x_position, 1200, ray_x_position, line_offset, f_color);
			// wall
			draw_line(game_planes->right_plane, ray_x_position, line_offset, ray_x_position, line_offset + line_height, color);
			// ceiling
			draw_line(game_planes->right_plane, ray_x_position, 0, ray_x_position, line_offset, c_color);
			//End of Drawing Walls
		}

}
