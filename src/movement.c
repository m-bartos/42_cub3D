/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 12:04:34 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
	game_t	*game;
	game = (game_t *)param;
	// starting player coordinates
	static double x = 600;
	static double y = 600;
	// delta x and y
	double pdx;
	double pdy;
	// initial player angle
	static int pa = 45;


	// double startX = 0.0;
	// double startY = 0.0;

	// double endX = 0;
	// double endY = 0;

	// initial angle
	pdx = cos(deg_to_rad(pa));
	pdy = sin(deg_to_rad(pa));

// Ignore for now - used by Player only
	// startX = x;
	// startY = y;
	// endX = x+pdx*100;
	// endY = y-pdy*100;

// planes
	planes_t *game_planes = game->game_planes;

////////////////////////////////////////////////////////////////////////////////
// Testing cleaning initial or previous screen - it works

	set_img_background(game_planes->left_plane, L_BACKGROUND);
	set_img_background(game_planes->right_plane, R_BACKGROUND);
	// int map[18][15] =
	// {
	// {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	// {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
	// {1,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
	// {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// };
	// draw_map(game_planes->left_plane, map);
	draw_map_char(game_planes->left_plane, game);

////////////////////////////////////////////////////////////////////////////////
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
	{
		x += pdy * 5;
		y += pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
	{
		x -= pdy * 5;
		y -= pdx * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		x += pdx * 5;
		y -= pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		x-= pdx * 5;
		y+= pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{
		pa += 5;
		pa = fix_ang(pa);
		pdx = cos(deg_to_rad(pa));
		pdy = sin(deg_to_rad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{
		pa -= 5;
		pa = fix_ang(pa);
		pdx = cos(deg_to_rad(pa));
		pdy = sin(deg_to_rad(pa));
	}
	// implement FOV
////////////////////////////////////////////////////////
// Ray casting rendering

	// Connect to the new game struct
	game->player.player_angle = pa;
	game->player.player_coordinates.x = x;
	game->player.player_coordinates.y = y;
	draw_rays(game);
	draw_player(game);
	draw_wall(game);
	// // for (int r = 0; r < 60; r++)
	// // {
	// // 	double h_distance = 0;
	// // 	double v_distance = 0;
	// // 	double fov = fix_ang((pa - 60 / 2) + r);

	// // 	point_t *hrc;
	// // 	point_t *vrc;
	// // 	player_t pl;
	// // 	pl.player_angle = pa;
	// // 	pl.player_angle = fov;
	// // 	//printf("Angle: %d\n", pl.player_angle);
	// // 	pl.player_coordinates.x = startX;
	// // 	pl.player_coordinates.y = startY;
	// // 	// Here change to v1
	// // 	// it consumes px, py, pa and map
	// // 	hrc = get_horizontal_ray_coordinates(&pl, map);
	// // 	vrc = get_vertical_ray_coordinates(&pl, map);


	// // 	// hrc = get_horizontal_ray_coordinates_v1(game);
	// // 	// vrc = get_vertical_ray_coordinates_v1(game);

	// // 	//printf("Func - Horizontal: Rx: %f, Ry: %f\n", hrc->x,hrc->y);
	// // 	//printf("Func - Vertical: Rx: %f, Ry: %f\n", vrc->x, vrc->y);

	// // 	h_distance = sqrt((hrc->x - pl.player_coordinates.x) * (hrc->x - pl.player_coordinates.x) + (hrc->y - pl.player_coordinates.y) * (hrc->y - pl.player_coordinates.y));
	// // 	v_distance = sqrt((vrc->x - pl.player_coordinates.x) * (vrc->x - pl.player_coordinates.x) + (vrc->y - pl.player_coordinates.y) * (vrc->y - pl.player_coordinates.y));
	// // 	if (v_distance < h_distance)
	// // 	{
	// // 		draw_line(game_planes->left_plane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, RAY);
	// // 		//draw_line(game_planes->right_plane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, color);
	// // 	}
	// // 	else
	// // 	{
	// // 		draw_line(game_planes->left_plane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, RAY);
	// // 		//draw_line(game_planes->right_plane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, color);
	// // 	}
	// // End of Ray Casting
	// /////////////////////////////////////////////////////////////////////
	// // Draw Wall
	// 	double corrected_distance;
	// 	if (v_distance < h_distance)
	// 		corrected_distance = v_distance * cos(deg_to_rad(fov - pa));
	// 	else
	// 		corrected_distance = h_distance * cos(deg_to_rad(fov - pa));

	// 	int screen_height = game->game_planes->right_plane->height;
	// 	int screen_width = game->game_planes->right_plane->width;
	// 	int max_wall_height = screen_height; // Wall extends the whole vertical line when directly facing

	// 	// Calculate the wall height based on the distance
	// 	// Adjust the wall size multiplyer to something appropriate like 64 or 128
	// 	int line_height = (64 * max_wall_height) / corrected_distance;
	// 	if (line_height > screen_height)
	// 		line_height = screen_height; // Ensure it doesn't exceed the screen height

	// 	int line_offset = (screen_height / 2) - (line_height / 2); // Centering the wall slice vertically

	// 	// Correct horizontal position for each ray
	// 	int ray_x_position = (screen_width - 16) - r * (screen_width / 60); // Inverted to draw from left to right

	// 	// Draw the wall slice by filling pixels vertically
	// 	// for (int y = line_offset; y < line_offset + line_height; y++)
	// 	//{
	// 	// 	mlx_put_pixel(game_planes->right_plane, ray_x_position, y, color);  // Draw at the correct x-coordinate
	// 	// }
	// 	for (int i = 0; i < 16; i++)
	// 	{
	// 		// floor
	// 		draw_line(game_planes->right_plane, ray_x_position, 1200, ray_x_position, line_offset, FLOOR);
	// 		// wall
	// 		draw_line(game_planes->right_plane, ray_x_position, line_offset, ray_x_position, line_offset + line_height, WALL);
	// 		// ceiling
	// 		draw_line(game_planes->right_plane, ray_x_position, 0, ray_x_position, line_offset, CEILING);
	// 		//End of Drawing Walls
	// 		ray_x_position += 1;
	// 	}
	// 	// // floor
	// 	// draw_line(game_planes->right_plane, ray_x_position, 1200, ray_x_position, line_offset, f_color);
	// 	// // wall
	// 	// draw_line(game_planes->right_plane, ray_x_position, line_offset, ray_x_position, line_offset + line_height, color);
	// 	// // ceiling
	// 	// draw_line(game_planes->right_plane, ray_x_position, 0, ray_x_position, line_offset, c_color);
	// 	//End of Drawing Walls
	// }

	// /////////////////////////////////////////////////////////////////////
	// // Draw player line
	// printf("Player Angle: %d\n", pa);
	// printf("PDX: %f\n", pdx);
	// printf("PDY: %f\n", pdy);
	// startX = x;
	// startY = y;
	// endX = x+pdx*100;
	// endY = y-pdy*100;
	// draw_line(game_planes->left_plane, startX, startY, endX, endY, PLAYER);
	// //draw_line(game_planes->right_plane, startX, startY, endX, endY, color);
}
