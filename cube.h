/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/23 15:35:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE

# include "./MLX42/include/MLX42/MLX42.h"
# include "./42_Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <string.h> // for memset

# define WIDTH 512
# define HEIGHT 512
# define SQUARE_SIZE 64

typedef struct point_s
{
	double	x;
	double	y;
}	point_t;

typedef struct player_location_s
{
	double		player_angle;
	double		fow;
	point_t		player_coordinates;
}	player_location_t;

typedef struct planes_s
{
	mlx_image_t *left_plane;
	mlx_image_t *right_plane;
} planes_t;

typedef struct map_s
{
	char	**map;
	int		width;
	int		height;
}	map_t;

typedef struct game_s
{
	player_location_t	player_location;
	planes_t			*game_planes;
	map_t				game_map;
}	game_t;

// MLX42 Drawing functions

//Bresenham’s line algorithm
void	draw_line(void *image, double startX, double startY, double endX, double endY, unsigned int color);

void	draw_square(mlx_image_t *image, int startX, int startY, unsigned int color);
void	put_square(mlx_image_t *image , point_t location, int32_t size, u_int32_t color);
void	set_img_background(mlx_image_t *image, int32_t color);

// Ray Casting
point_t *get_horizontal_ray_coordinates(player_location_t *pl, int map[18][15]);
point_t *get_vertical_ray_coordinates(player_location_t *pl, int map[18][15]);
point_t *get_vertical_ray_coordinates_v1(game_t *game);
point_t *get_horizontal_ray_coordinates_v1(game_t *game);
double	get_point_distance(game_t *game, point_t *coordinates);
void	draw_rays(game_t *game);

// Game
void	draw_map(mlx_image_t *image, int arr[18][15]);
void	move_player(mlx_key_data_t key, void *param);


// Utils
float			deg_to_rad(int a);
int				fix_ang(int a);
u_int32_t		get_rgba(u_int32_t r, u_int32_t g, u_int32_t b, u_int32_t a);
int				load_map(char *map_str, game_t *game);
void			draw_map_char(mlx_image_t *image, game_t *game);

#endif
