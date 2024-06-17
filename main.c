/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/17 19:55:34 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube.h"


// Draw a Window with gray background

// Draw a player - 10 x 10 pixels dot.

// How to draw player in MLX? Use image with size

unsigned int get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return ((unsigned int) r << 24 | (unsigned int) g << 16 | (unsigned int) b << 8 | (unsigned int)a);
}


void	clear_square(mlx_image_t *image, int x, int y)
{
	int SQUARE_SIZE = 64;
	unsigned int b_color = get_rgba(0, 10, 139, 255);

	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_SIZE; j++)
		{
			mlx_put_pixel(image, x + i, y + j, b_color); // White square
		}
	}
}

void	move_player(mlx_key_data_t key, void *param)
{
	// starting player coordinates
	static int x = 600;
	static int y = 600;
	unsigned int color = get_rgba(0, 255, 0, 255);
	mlx_image_t *background = (mlx_image_t *) param;
	clear_square(background, x, y);
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
		x += 5;
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
		x -= 5;
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
		y -= 5;
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
		y += 5;
	draw_square(background, x, y, color);
}

// void rotate_player(mlx_key_data_t key, void *param)
// {
// 	// starting player coordinates
// 	static int x = 600;
// 	static int y = 600;
// 	unsigned int color = get_rgba(0, 255, 0, 255);
// 	mlx_image_t *background = (mlx_image_t *) param;

// 	if (key.action == MLX_PRESS || key.action == MLX_REPEAT && key.key == MLX_KEY_LEFT)
// 	{
// 		// rotate to left
// 		;
// 	}

// 		if (key.action == MLX_PRESS || key.action == MLX_REPEAT && key.key == MLX_KEY_RIGHT)
// 	{
// 		// rotate to right
// 		;
// 	}
// }


void	draw_map(mlx_image_t *image, int arr[18][30])
{
	(void) image;
	unsigned int color = get_rgba(255, 0, 0, 255);
	int s_size = 64;
	int y_map_size = 18;
	int x_map_size = 30;
	int y = 0;
	// draws y axes
	while (y < y_map_size)
	{
		int x = 0;
		// draws x axes
		while (x < x_map_size)
		{
			printf("%d", arr[y][x]);
			if (arr[y][x] == 1)
			{
				draw_square(image, x * s_size, y * s_size, color);
			}
			x++;
		}
		printf("\n");
		y++;
	}
}

int	main(void)
{
	int w = 1920;
	int h = 1200;
	//unsigned int p_color = get_rgba(255, 255, 0, 255);
	unsigned int b_color = get_rgba(0, 10, 139, 255);
	unsigned int p_color = get_rgba(0, 255, 0, 255);
	#define BPP sizeof(int32_t)
	mlx_t *mlx;
	mlx = mlx_init(w, h, "Ray Caster", true);
	mlx_keyfunc ecs_key = move_player;

	// Create image (bacground) over the whole window
	mlx_image_t* background = mlx_new_image(mlx, w, h);
	mlx_image_to_window(mlx, background, 0, 0);

	// Set pixels over the entire picture (background)
	// width
	for (int x = 0; x < w; x++)
	{
		// height
		for (int y = 0; y < h; y++)
		{
			//printf("%d\n", x);
			mlx_put_pixel(background, x, y, b_color);
		}
	}


	int map[18][30] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	draw_square(background, 600, 600, p_color);
	draw_map(background, map);

	for (int i = 0; i < 400; i++)
	{
		draw_line(background, 200, 200, 10+i, 25, get_rgba(255, 192, 203, 255));
		draw_line(background, 400, 400, 210+i, 225, get_rgba(255, 192, 203, 255));

	}
	// Key HOOK
	mlx_key_hook(mlx, ecs_key, background);
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
