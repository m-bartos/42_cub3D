/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 13:41:20 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
	// starting player coordinates
	static double x = 600;
	static double y = 600;
	// delta x and y
	double pdx;
	double pdy;
	// initial player angle
	static int pa = 90;


	double startX = 0.0;
	double startY = 0.0;

	double endX = 0;
	double endY = 0;

	// initial angle ??
	pdx = cos(degToRad(pa));
	pdy = sin(degToRad(pa));

	startX = x;
	startY = y;
	endX = x+pdx*100;
	endY = y-pdy*100;
// color and planes
	unsigned int color = get_rgba(0, 255, 0, 255);
	planes_t *game_planes = (planes_t *) param;
////////////////////////////////////////////////////////////////////////////////
// Testing cleaning initial or previous screen - it works
	int l_color = get_rgba(0, 10, 139, 255);
	int r_color = get_rgba(0, 0, 0, 255);
	for (int x = 0; x < 960; x++)
	{
		// height
		for (int y = 0; y < 1200; y++)
		{
			//printf("%d\n", x);
			mlx_put_pixel(game_planes->left_pane, x, y, l_color);
			mlx_put_pixel(game_planes->right_pane, x, y, r_color);
		}
	}

	int map[18][15] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
	{1,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	draw_map(game_planes->left_pane, map);
	//draw_map(game_planes->right_pane, map);
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
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = sin(degToRad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = sin(degToRad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_X)
	{
		printf("You pressed X\n");
	}

	// implement FOV
////////////////////////////////////////////////////////
// Ray casting rendering
	for (int r = 0; r < 60; r++)
	{
		double h_distance = 0;
		double v_distance = 0;
		double fov = FixAng((pa - 60 / 2) + r);
		//printf("TEST:::%f\n", fov);
		point_t *hrc;
		point_t *vrc;
		player_location_t pl;
		pl.player_angle = pa;
		pl.player_angle = fov;
		//printf("Angle: %d\n", pl.player_angle);
		pl.player_coordinates.x = startX;
		pl.player_coordinates.y = startY;
		hrc = get_horizontal_ray_coordinates(&pl, map);
		vrc = get_vertical_ray_coordinates(&pl, map);

		//printf("Func - Horizontal: Rx: %f, Ry: %f\n", hrc->x,hrc->y);
		//printf("Func - Vertical: Rx: %f, Ry: %f\n", vrc->x, vrc->y);

		h_distance = sqrt((hrc->x - pl.player_coordinates.x) * (hrc->x - pl.player_coordinates.x) + (hrc->y - pl.player_coordinates.y) * (hrc->y - pl.player_coordinates.y));
		v_distance = sqrt((vrc->x - pl.player_coordinates.x) * (vrc->x - pl.player_coordinates.x) + (vrc->y - pl.player_coordinates.y) * (vrc->y - pl.player_coordinates.y));

		//printf("Horizontal Distance: %f\n", h_distance);
		//printf("Vertical Distance: %f\n", v_distance);
		int ppp_color = get_rgba(0, 0, 0, 255);
		if (v_distance < h_distance)
		{
			draw_line(game_planes->left_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
			//draw_line(game_planes->right_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, color);
		}
		else
		{
			draw_line(game_planes->left_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
			//draw_line(game_planes->right_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, color);
		}
	// End of Ray Casting
	/////////////////////////////////////////////////////////////////////
	// Draw Wall
		double corrected_distance;
		if (v_distance < h_distance)
			corrected_distance = v_distance * cos(degToRad(fov - pa));
		else
			corrected_distance = h_distance * cos(degToRad(fov - pa));

		int screen_height = 1200;
		int screen_width = 960;
		int max_wall_height = screen_height; // Wall extends the whole vertical line when directly facing

		// Calculate the wall height based on the distance
		// Adjust the wall size multiplyer to something appropriate like 64 or 128
		int line_height = (64 * max_wall_height) / corrected_distance;
		if (line_height > screen_height)
			line_height = screen_height; // Ensure it doesn't exceed the screen height

		int line_offset = (screen_height / 2) - (line_height / 2); // Centering the wall slice vertically

		// Correct horizontal position for each ray
		int ray_x_position = (screen_width - 1) - r * (screen_width / 60); // Inverted to draw from left to right

		// Draw the wall slice by filling pixels vertically
		// for (int y = line_offset; y < line_offset + line_height; y++)
		//{
		// 	mlx_put_pixel(game_planes->right_pane, ray_x_position, y, color);  // Draw at the correct x-coordinate
		// }
		draw_line(game_planes->right_pane, ray_x_position, line_offset, ray_x_position, line_offset + line_height, color);
	}

	/////////////////////////////////////////////////////////////////////
	// Draw player line
	printf("Player Angle: %d\n", pa);
	printf("PDX: %f\n", pdx);
	printf("PDY: %f\n", pdy);
	startX = x;
	startY = y;
	endX = x+pdx*100;
	endY = y-pdy*100;
	draw_line(game_planes->left_pane, startX, startY, endX, endY, color);
	//draw_line(game_planes->right_pane, startX, startY, endX, endY, color);
}
