/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/28 16:25:47 by mbartos          ###   ########.fr       */
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
		// Think about it r <== screen_width to get really 60 degree FOV
		for (int r = 0; r <= screen_width; r++)
		{
			// calculate agle for the 60 fov
			game->player.player_angle = fix_ang((pa - fov / 2) + r * angle_increment);
			if (r == 0 || r == screen_width)
				printf("R: %d, RA: %f\n", r, game->player.player_angle);
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
			double old_line_height = line_height;
			if (line_height > screen_height)
				line_height = screen_height; // Ensure it doesn't exceed the screen height
			 // Centering the wall slice vertically = offset that is same above the wall and below it
			double line_offset = (screen_height / 2) - (line_height / 2);
			int ray_x_position = WINDOW_WIDTH - r;
			//////////////////////////////////////////////////////////////////////
			// Textures

			mlx_texture_t  *wall;
			wall = get_texture(game, h_distance, v_distance);
			double	texture_x;
			if (v_distance < h_distance)
			{
				texture_x = vrc->y - floor(vrc->y / SQUARE_SIZE) * SQUARE_SIZE;
			}
			else
			{
				texture_x = hrc->x - floor(hrc->x / SQUARE_SIZE) * SQUARE_SIZE;
			}
			int texture_x_index = (int)texture_x * wall->width / SQUARE_SIZE;

			int texture_y_index;
			// Draw the wall slice with texture mapping
        	for (int y = 0; y < line_height; y++)
			{
				double texture_y_ratio = wall->height / old_line_height; // it determines the ratio between unit of the line
				if (old_line_height > screen_height)
					texture_y_index = (int)((y + (old_line_height - screen_height) / 2) * texture_y_ratio); // calculates y position of the pixel
				else
					texture_y_index = (int)(texture_y_ratio * y); // calculates y position of the pixel
				// test the pixel color from the coordinates
				unsigned int color = get_pixel_color(wall, texture_y_index, texture_x_index);
				mlx_put_pixel(game_planes->game_plane, ray_x_position, (int)(line_offset + y), color);
			}

			// End of textures
			//////////////////////////////////////////////////////////////////////
			// floor
			// draw_line(game_planes->game_plane, ray_x_position, WINDOW_HEIGHT, ray_x_position, WINDOW_HEIGHT - round(line_offset), FLOOR);
			// wall
			//draw_line(game_planes->game_plane, ray_x_position, line_offset, ray_x_position, round (line_offset + line_height), WALL);
			// ceiling
			// draw_line(game_planes->game_plane, ray_x_position, 0, ray_x_position, round(line_offset), CEILING);
		}
		game->player.player_angle = pa;
}


/*
	Get the texture that was hit with the ray, only 4 textures are available, for each cardinal direction.
	Done
	On the texture get the exact spot where it was hit and extract the vertical values from the texture
	Not done
	The vertical line height is already calculcated so add the values to it and draw it.
	This does not seeem right.

*/
