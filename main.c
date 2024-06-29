/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 17:53:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cube.h"

mlx_t	*setup_mlx(void)
{
	mlx_t	*mlx;
	int		screen_x;
	int		screen_y;
	int		w;
	int		h;

	w = WINDOW_WIDTH;
	h = WINDOW_HEIGHT;
	mlx = mlx_init(w, h, "Ray Caster", true);
	mlx_get_monitor_size(0, &screen_x, &screen_y);
	mlx_set_window_pos(mlx, screen_x / 2 - w / 2, screen_y / 2 - h / 2);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	return (mlx);
}

void	init_structs(game_t *game, map_t *map, planes_t *planes, char *path)
{
	*game = (game_t){0};
	init_map(map);
	game->player = map->player;
	game->map = map;
	game->planes = planes;
	fill_map_struct(map, path);
}

int	main(int argc, char **argv)
{
	map_t		map;
	mlx_t		*mlx;
	mlx_keyfunc	move_p_func;
	planes_t	planes;
	game_t		game;

	error_argc(argc);
	init_structs(&game, &map, &planes, argv[1]);
	mlx = setup_mlx();
	move_p_func = move_player;
	planes.game_plane = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, planes.game_plane, 0, 0);
	set_img_background(planes.game_plane, R_BACKGROUND);
	draw_wall(&game);
	//draw_map(planes.game_plane, &game);
	//draw_rays(&game);
	mlx_key_hook(mlx, move_p_func, &game);
	mlx_loop(mlx);
	// Cleaning func
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	clean_map(NULL);
	return (0);
}
