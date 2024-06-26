/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/26 13:29:38 by orezek           ###   ########.fr       */
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

		// get screen size
		int screen_height = game->game_planes->game_plane->height;
		int screen_width = game->game_planes->game_plane->width;
		// set initial player angle
		pa = game->player.player_angle;
		// set images to draw lines
		game_planes =  game->game_planes;
		// set field of view = the number of lines per width of the screen
		// you need to get for every line a different angle
		fov = game->player.fov;

		// Angle increment
		double angle_increment = fov / screen_width;
		for (int r = 0; r < screen_width; r++)
		{
			// calculate agle for the 60 fov
			game->player.player_angle = fix_ang((pa - fov / 2) + r * angle_increment);
			// cast ray and get horizontal coordiantes
			hrc = get_horizontal_ray_coordinates(game);
			// cast ray and get vertical coordinates
			vrc = get_vertical_ray_coordinates(game);
			// get horizontal distance between the two points
			h_distance = get_point_distance(game, hrc);
			// get vertical distance between the two points
			v_distance = get_point_distance(game, vrc);
			// choose shorter distance
			if (v_distance < h_distance)
				corrected_distance = v_distance * cos(deg_to_rad(game->player.player_angle - pa));
			else
				corrected_distance = h_distance * cos(deg_to_rad(game->player.player_angle - pa));
			// set max wall height
			double max_wall_height = screen_height; // Wall extends the whole vertical line when directly facing

			// Calculate the wall height based on the distance
			// Adjust the wall size multiplyer to something appropriate like 64 or 128
			double line_height = (SQUARE_SIZE * max_wall_height) / corrected_distance;
			if (line_height > screen_height)
				line_height = screen_height; // Ensure it doesn't exceed the screen height
			 // Centering the wall slice vertically = offset that is same above the wall and below it
			double line_offset = (screen_height / 2) - (line_height / 2);
			int ray_x_position = WINDOW_WIDTH - r;
			draw_line(game_planes->game_plane, ray_x_position, WINDOW_HEIGHT, ray_x_position, round(line_offset), FLOOR);
			// wall
			draw_line(game_planes->game_plane, ray_x_position, line_offset, ray_x_position, round (line_offset + line_height), WALL);
			// ceiling
			draw_line(game_planes->game_plane, ray_x_position, 0, ray_x_position, round(line_offset), CEILING);
		}
		game->player.player_angle = pa;
}
