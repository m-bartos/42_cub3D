/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 13:03:38 by orezek           ###   ########.fr       */
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

		// set initial player angle
		pa = game->player.player_angle;
		printf("INIT:PA: %f\n", pa);
		// set images to draw lines
		game_planes =  game->game_planes;
		// set field of view = the number of lines per width of the screen
		// you need to get for every line a different angle
		fov = game->player.fow;
		for (int r = 0; r < fov; r++)
		{
			// calculate agle for the 60 fov
			game->player.player_angle = fix_ang((pa - fov / 2) + r);
			// cast ray and get horizontal coordiantes
			hrc = get_horizontal_ray_coordinates_v1(game);
			// cast ray and get vertical coordinates
			vrc = get_vertical_ray_coordinates_v1(game);
			// get horizontal distance between the two points
			h_distance = get_point_distance(game, hrc);
			// get vertical distance between the two points
			v_distance = get_point_distance(game, vrc);
			// choose shorter distance
			if (v_distance < h_distance)
				corrected_distance = v_distance * cos(deg_to_rad(game->player.player_angle - pa));
			else
				corrected_distance = h_distance * cos(deg_to_rad(game->player.player_angle - pa));
			// get screen size
			int screen_height = game->game_planes->right_plane->height;
			int screen_width = game->game_planes->right_plane->width;
			// set max wall height
			int max_wall_height = screen_height; // Wall extends the whole vertical line when directly facing

			// Calculate the wall height based on the distance
			// Adjust the wall size multiplyer to something appropriate like 64 or 128
			int line_height = (64 * max_wall_height) / corrected_distance;
			if (line_height > screen_height)
				line_height = screen_height; // Ensure it doesn't exceed the screen height
			 // Centering the wall slice vertically = offset that is same above the wall and below it
			int line_offset = (screen_height / 2) - (line_height / 2);
			// Correct horizontal position for each ray
			int ray_x_position = (screen_width - 16) - r * (screen_width / fov); // Inverted to draw from left to right
			//printf("Xray: %d\n", ray_x_position);
			// Test to fill in all pixels: Note: number of new lines after ray_x_position (16) currently has to be the same offset from the right (screen_width - 16)
			for (int i = 0; i < 16; i++)
			{
				// floor
				draw_line(game_planes->right_plane, ray_x_position, 1200, ray_x_position, line_offset, FLOOR);
				// wall
				draw_line(game_planes->right_plane, ray_x_position, line_offset, ray_x_position, line_offset + line_height, WALL);
				// ceiling
				draw_line(game_planes->right_plane, ray_x_position, 0, ray_x_position, line_offset, CEILING);
				//End of Drawing Walls
				ray_x_position += 1;
			}
		}
		game->player.player_angle = pa;
		printf("END:PA: %f\n", pa);
}
