/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:52 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 17:27:24 by orezek           ###   ########.fr       */
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
	mlx = mlx_init(w, h, "Cub3D", true);
	mlx_get_monitor_size(0, &screen_x, &screen_y);
	mlx_set_window_pos(mlx, screen_x / 2 - w / 2, screen_y / 2 - h / 2);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	return (mlx);
}

void	init_structs(t_game *game, t_map *map, t_planes *planes, char *path)
{
	*game = (t_game){0};
	init_map(map);
	game->player = map->player;
	game->map = map;
	game->planes = planes;
	fill_map_struct(map, path);
	change_player_coordinates_format(map->player);
}

int	main(int argc, char **argv)
{
	t_map		map;
	mlx_t		*mlx;
	mlx_keyfunc	move_p_func;
	t_planes	planes;
	t_game		game;

	error_argc(argc);
	init_structs(&game, &map, &planes, argv[1]);
	mlx = setup_mlx();
	game.mlx = mlx;
	move_p_func = move_player;
	planes.game_plane = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, planes.game_plane, 0, 0);
	set_img_background(planes.game_plane, R_BACKGROUND);
	draw_wall(&game);
	mlx_key_hook(mlx, move_p_func, &game);
	mlx_loop(mlx);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	clean_map(NULL);
	return (EXIT_SUCCESS);
}
