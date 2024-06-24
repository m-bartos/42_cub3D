/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 20:23:06 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube.h"

char *static_map = 	"111111111111111\n"
					"100000000000001\n"
					"100100000111001\n"
					"100100000000001\n"
					"100100000000001\n"
					"100100000000001\n"
					"110000000000001\n"
					"100000000000001\n"
					"100000000000001\n"
					"100000001000001\n"
					"100000000000001\n"
					"100000000000001\n"
					"100000000000001\n"
					"100000000000001\n"
					"100000000011111\n"
					"100111100000001\n"
					"100000000000001\n"
					"111111111111111\n";

int	main(void)
{
	// Load a map from a string
	char **game_map = ft_split(static_map, '\n');
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
	mlx_image_t	*left_plane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, left_plane, 0, 0);

	// Image declaration for right side of the screen
	mlx_image_t	*right_plane = mlx_new_image(mlx, w/2, h);
	mlx_image_to_window(mlx, right_plane, w/2, 0);

	planes_t game_planes;
	game_planes.left_plane = left_plane;
	game_planes.right_plane = right_plane;
	// Set color over two images
	// Each image has its own coordinates starting 0, 0.
	//set_img_background(game_planes.left_plane, game_planes.left_plane, l_color, r_color);
	set_img_background(left_plane, l_color);
	set_img_background(right_plane, r_color);

	// Init the game
	game_t game;
	game = (game_t){0};
	game.game_planes = &game_planes;
	game.player.player_angle = 90;
	game.player.coordinates.x = 600;
	game.player.coordinates.y = 600;
	game.player.fov = 60;
	game.game_map.map = game_map;

	load_map(static_map, &game);
	draw_map(left_plane, &game);

	////////////////////////////////////////////////////////
	// Ray casting rendering
	// Only cast rays ,take player x, y and an angle cat rays in FOV in a way they end in the wall
	draw_rays(&game);
	draw_player(&game);
	draw_wall(&game);
	// End of Ray Casting
	/////////////////////////////////////////////////////////////////////
	// Key HOOK
	mlx_key_hook(mlx, move_p_func, &game);
	// Game LOOP
	mlx_loop(mlx);
	// Cleaning func
	mlx_terminate(mlx);

}

