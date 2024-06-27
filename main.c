/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/27 17:58:21 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube.h"

char *static_map = 	"111111111111111111\n"
					"100000000000000001\n"
					"100100000111000001\n"
					"100100000000000001\n"
					"100100000000000001\n"
					"100100000000000001\n"
					"110000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000001000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000000001\n"
					"100000000000011111\n"
					"100111100000000001\n"
					"100000000000000001\n"
					"111111111111111111\n";

int	main(void)
{
	// Window Size
	int w = WINDOW_WIDTH;
	int h = WINDOW_HEIGHT;

	int screen_x;
	int screen_y;

	// Mlx main struct declaration
	mlx_t *mlx;
	// Mlx window setup
	mlx = mlx_init(w, h, "Ray Caster", true);
	mlx_get_monitor_size(0, &screen_x, &screen_y);
	mlx_set_window_pos(mlx, screen_x / 2 - w/2, screen_y / 2 - h/2);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	// Mlx key func initialization
	mlx_keyfunc move_p_func = move_player;

	// // Image declaration for the whole game
	mlx_image_t	*game_img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, game_img, 0, 0);

	// Texture test image for testing the png files and image buffers
	//mlx_image_t *texture_img = mlx_new_image(mlx, 1200, 800);

	// Add the image to game_planes struct and initialize background color
	planes_t game_planes;
	game_planes.game_plane = game_img;
	set_img_background(game_img, R_BACKGROUND);

	// Declare texture variables
	// mlx_texture_t	*prague;
	// mlx_texture_t	*brno;
	// mlx_texture_t	*olomouc;
	// mlx_texture_t	*ostrava;
	mlx_texture_t	*wall;
	// Load PNG files and return textures
	// prague = mlx_load_png(PRAGUE);
	// brno = mlx_load_png(BRNO);
	// olomouc = mlx_load_png(OLOMOUC);
	// ostrava = mlx_load_png(OSTRAVA);
	wall = mlx_load_png(B_WALL);
	//texture_img = mlx_texture_to_image(mlx, wall);
	//mlx_image_to_window(mlx, texture_img, 0,0);
	// Init the game
	game_t game;
	game = (game_t){0};
	load_map(static_map, &game);
	game.game_planes = &game_planes;
	game.player.player_angle = 33;
	game.player.coordinates.x = 600;
	game.player.coordinates.y = 600;
	game.player.fov = 60;
	game.game_map.square_size = SQUARE_SIZE;
	// Add textures to the game struct
	// game.game_map.game_textures->prague = prague;
	// game.game_map.game_textures->brno = brno;
	// game.game_map.game_textures->olomouc = olomouc;
	// game.game_map.game_textures->ostrava = ostrava;
	game.game_map.game_textures.wall = wall;


	// Draw initial 3d scene.
	draw_wall(&game);
	// printf("Test\n");
	// exit(1);
	// Key HOOK
	mlx_key_hook(mlx, move_p_func, &game);
	// Game LOOP
	mlx_loop(mlx);
	// Cleaning func
	mlx_terminate(mlx);
	/*
	Todo:
	1) refactor draw rays
	2) refactor draw walls - especially ray caster, wall drawing
	1) clean memory
		a) map
		b) return form ray_cast_ver and hor
	2) parser
	3) dynamic minimap scaling
	6) Wall collisions
	*/
}

