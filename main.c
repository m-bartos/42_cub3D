/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 17:02:37 by mbartos          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	map_t 		map;

	error_argc(argc);
	init_map(&map);
	fill_map_struct(&map, argv[1]);
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

	// Add the image to planes struct and initialize background color
	planes_t planes;
	planes.game_plane = game_img;
	set_img_background(game_img, R_BACKGROUND);

	// Declare texture variables
	// mlx_texture_t	*west;
	// mlx_texture_t	*east;
	// mlx_texture_t	*north;
	// mlx_texture_t	*south;
	// Load PNG files and return textures
	// west = mlx_load_png(WEST);
	// east = mlx_load_png(EAST);
	// north = mlx_load_png(NORTH);
	// south = mlx_load_png(SOUTH);
	// Init the game
	game_t game;
	// textures_t txts;
	game = (game_t){0};
	// load_map(static_map, &game);
	// exit(77);
	game.player = map.player;
	game.map = &map;
	game.planes = &planes;
	// game.player->angle = 90;
	// game.player->coordinates.x = 300;
	// game.player->coordinates.y = 300;
	// game.player->fov = 60;
	// game.map->square_size = SQUARE_SIZE;
	//////////////////////////////////////
	// New implementation
	// game.map.game_textures.angle_270 = west;
	// game.map.game_textures.angle_90 = east;
	// game.map.game_textures.angle_0 = north;
	// game.map.game_textures.angle_180 = south;
	// txts.angle_270 = west;
	// txts.angle_90 = east;
	// txts.angle_0 = north;
	// txts.angle_180 = south;
	// game.map->txts = &txts;
	//////////////////////////////////////
	// Test
	// printf("West: %d\n", game.map->txts->angle_270->width);
	// printf("East: %d\n", game.map->txts->angle_90->width);
	// printf("North: %d\n", game.map->txts->angle_0->width);
	// printf("South: %d\n", game.map->txts->angle_180->width);
	//////////////////////////////////////
	//////////////////////////////////////
	// Previous implementation
	// Add textures to the game struct
	// game.map.game_textures.we = west;
	// game.map.game_textures.ea = east;
	// game.map.game_textures.no = north;
	// game.map.game_textures.so = south;
	//////////////////////////////////////
	// Draw initial 3d scene.
	draw_wall(&game);
	// exit(55);
	// printf("Test\n");
	// exit(1);
	// Key HOOK
	//draw_map(game_img, &game);
	//draw_rays(&game);
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
	7) Textures with directions
	*/
	// clean_map(NULL);
}

