/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/22 19:14:41 by orezek           ###   ########.fr       */
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
				draw_square(image, x * s_size, y * s_size, w_color);
			}
			else
				draw_square(image, x * s_size, y * s_size, f_color);
			x++;
		}
		//printf("\n");
		y++;
	}
}

// void	move_player(mlx_key_data_t key, void *param)
// {
// 	// starting player coordinates
// 	static double x = 600;
// 	static double y = 600;
// 	static double pdx;
// 	static double pdy;
// 	static int pa = 90;

// 	int startX = 0;
// 	int startY = 0;

// 	int endX = 0;
// 	int endY = 0;

// 	pdx = cos(deg_to_rad(pa));
// 	pdy = sin(deg_to_rad(pa));
// 	unsigned int color = get_rgba(0, 255, 0, 255);
// 	mlx_image_t *background = (mlx_image_t *) param;
// 	//clear_square(background, x, y);
// 	startX = round(x);
// 	startY = round(y);
// 	endX = round(x+pdx*100);
// 	endY = round(y+pdy*100);
// 	printf("XPDX: %f YXPX: %f\n", x+pdx*100, y+pdy*100);
// 	// clean line
// 	draw_line(background, startX, startY, endX, endY, get_rgba(255, 255, 255, 255));
// 	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
// 		x += 25;
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
// 		x -= 25;
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
// 	{
// 		x += pdx * 5;
// 		y += pdy * 5;
// 	}
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
// 	{
// 		x-= pdx * 5;
// 		y-= pdy * 5;
// 	}
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
// 	{
// 		pa -= 5;
// 		pa = fix_ang(pa);
// 		pdx = cos(deg_to_rad(pa));
// 		pdy = sin(deg_to_rad(pa));
// 		printf("LX: %f\n", x);
// 		printf("LY: %f\n", x);
// 		printf("LPA: %d\n", pa);
// 		printf("LPDX: %f\n", pdx);
// 		printf("LPDY: %f\n", pdy);
// 	}
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
// 	{
// 		pa += 5;
// 		pa = fix_ang(pa);
// 		pdx = cos(deg_to_rad(pa));
// 		pdy = sin(deg_to_rad(pa));
// 		printf("RX: %f\n", x);
// 		printf("RY: %f\n", x);
// 		printf("RPA: %d\n", pa);
// 		printf("RPDX: %f\n", pdx);
// 		printf("RPDY: %f\n", pdy);
// 	}
// 	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_X)
// 	{
// 		int l_color = get_rgba(0, 10, 139, 255);
// 		for (int x = 0; x < 960; x++)
// 		{
// 			// height
// 			for (int y = 0; y < 1200; y++)
// 			{
// 				//printf("%d\n", x);
// 				mlx_put_pixel(background, x, y, l_color);
// 			}
// 		}

// 		int map[18][15] =
// 		{
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
// 		{1,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		};
// 		draw_map(background, map);
// 		printf("X pressed or hold!\n");
// 	}
// 	//draw_square(background, x, y, color);
// 	startX = round(x);
// 	startY = round(y);
// 	endX = round(x+pdx*100);
// 	endY = round(y+pdy*100);
// 	draw_line(background, startX, startY, endX, endY, color);
// 	// printf("StartX: %f\n", x+pdx);
// 	// printf("StartY: %f\n", y+pdy);
// 	// printf("EndX: %f\n", x+pdx*100);
// 	// printf("EndY: %f\n", y+pdy*100);
// }



void	set_background(mlx_image_t *left_pane, mlx_image_t *right_pane, int l_color, int r_color)
{
	for (int x = 0; x < 960; x++)
	{
		// height
		for (int y = 0; y < 1200; y++)
		{
			//printf("%d\n", x);
			mlx_put_pixel(left_pane, x, y, l_color);
			mlx_put_pixel(right_pane, x, y, r_color);
		}
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
	mlx_image_t* left_pane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, left_pane, 0, 0);

	// Image declaration for right side of the screen
	mlx_image_t *right_pane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, right_pane, w/2, 0);

	planes_t game_planes;
	game_planes.left_pane = left_pane;
	game_planes.right_pane = right_pane;
	// Set color over two images
	// Each image has its own coordinates starting 0, 0.
	set_background(game_planes.left_pane, game_planes.left_pane, l_color, r_color);

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

	draw_map(left_pane, map);
	//draw_map(right_pane, map);
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
		draw_line(left_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
		//draw_line(right_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
	}
	else
	{
		draw_line(left_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
		//draw_line(right_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
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




// Libft Test

// int	main(void)
// {
// 	char *test = "Hello Cube!";
// 	char *str = ft_strdup(test);

// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }

// MLX42 Test

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}

// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
