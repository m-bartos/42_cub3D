/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 21:18:37 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube.h"


// Draw a Window with gray background

// Draw a player - 10 x 10 pixels dot.

// How to draw player in MLX? Use image with size

// unsigned int get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
// {
// 	return ((unsigned int) r << 24 | (unsigned int) g << 16 | (unsigned int) b << 8 | (unsigned int)a);
// }


void	clear_square(mlx_image_t *image, int x, int y)
{
	unsigned int b_color = get_rgba(0, 10, 139, 255);

	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_SIZE; j++)
		{
			mlx_put_pixel(image, x + i, y + j, b_color); // White square
		}
	}
}


void	draw_map(mlx_image_t *image, int arr[18][15])
{
	// red color
	unsigned int w_color = get_rgba(255, 0, 0, 255);
	//
	unsigned int f_color = get_rgba(255, 255, 255, 255);
	int s_size = 64;
	int y_map_size = 18;
	int x_map_size = 15;
	int y = 0;
	// draws y axes
	while (y < y_map_size)
	{
		int x = 0;
		// draws x axes
		while (x < x_map_size)
		{
			//printf("%d", arr[y][x]);
			if (arr[y][x] == 1)
			{
				//draw_square(image, x * s_size, y * s_size, w_color);
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, w_color);
			}
			else
				//draw_square(image, x * s_size, y * s_size, f_color);
				put_square(image, (point_t){.x = x * s_size, .y = y * s_size}, s_size, f_color);
			x++;
		}
		//printf("\n");
		y++;
	}
}


int	main(void)
{
	// ??
	#define BPP sizeof(int32_t)
	// Window Size
	int w = 1920;
	int h = 1200;
	// Pane colors
	// blue
	unsigned int l_color = get_rgba(0, 10, 139, 255);
	// black
	unsigned int r_color = get_rgba(0, 0, 0, 255);

	// Mlx main struct declaration
	mlx_t *mlx;
	// Mlx window setup
	mlx = mlx_init(w, h, "Ray Caster", true);

	// Mlx key func initialization
	mlx_keyfunc move_p_func = move_player;

	// Image declaration for left side of the screen
	mlx_image_t* left_plane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, left_plane, 0, 0);

	// Image declaration for right side of the screen
	mlx_image_t *right_plane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, right_plane, w/2, 0);

	planes_t game_planes;
	game_planes.left_plane = left_plane;
	game_planes.right_plane = right_plane;
	// Set color over two images
	// Each image has its own coordinates starting 0, 0.
	//set_background(game_planes.left_plane, game_planes.left_plane, l_color, r_color);
	set_background(left_plane, l_color);
	set_background(right_plane, r_color);

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

	draw_map(left_plane, map);
	//draw_map(right_plane, map);
//////////////////////////////////////////////////////
	// Ray Casting
	double h_distance = 0;
	double v_distance = 0;

	point_t *hrc;
	point_t *vrc;
	player_location_t pl;
	pl.player_angle = 90;
	pl.player_coordinates.x = 600;
	pl.player_coordinates.y = 600;
	hrc = get_horizontal_ray_coordinates(&pl, map);
	vrc = get_vertical_ray_coordinates(&pl, map);

	printf("Func - Horizontal: Rx: %f, Ry: %f\n", hrc->x,hrc->y);
	printf("Func - Vertical: Rx: %f, Ry: %f\n", vrc->x, vrc->y);

	h_distance = sqrt((hrc->x - pl.player_coordinates.x) * (hrc->x - pl.player_coordinates.x) + (hrc->y - pl.player_coordinates.y) * (hrc->y - pl.player_coordinates.y));

	v_distance = sqrt((vrc->x - pl.player_coordinates.x) * (vrc->x - pl.player_coordinates.x) + (vrc->y - pl.player_coordinates.y) * (vrc->y - pl.player_coordinates.y));
	printf("Horizontal Distance: %f\n", h_distance);
	printf("Vertical Distance: %f\n", v_distance);
	int ppp_color = get_rgba(0, 0, 0, 255);
	if (v_distance < h_distance)
	{
		draw_line(left_plane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
		//draw_line(right_plane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
	}
	else
	{
		draw_line(left_plane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
		//draw_line(right_plane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
	}
// End of Ray Casting
////////////////////////////////////////////////////////////
	// Key HOOK
	mlx_key_hook(mlx, move_p_func, &game_planes);
	// Game LOOP
	mlx_loop(mlx);
	// Cleaning func
	mlx_terminate(mlx);

}

