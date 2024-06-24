/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/24 20:25:43 by orezek           ###   ########.fr       */
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

// Size of the map - not used now
# define WIDTH 512
# define HEIGHT 512
# define SQUARE_SIZE 64

// Define the pixel change when key is pressed
# define KEY_PRESS 5

#define PLAYER_LENGTH 100

// Color constants
# define FLOOR get_rgba(101, 67, 33, 255)
# define CEILING get_rgba(0, 0, 255, 255)
# define WALL get_rgba(0, 255, 0, 255)
# define RAY get_rgba(0, 0, 0, 255)
# define PLAYER get_rgba(0, 255, 0, 255)
# define L_BACKGROUND get_rgba(0, 10, 139, 255)
# define R_BACKGROUND get_rgba(0, 0, 0, 255)
# define MINI_WALL get_rgba(255, 0, 0, 255)
# define MINI_FLOOR get_rgba(255, 255, 255, 255)

typedef struct point_s
{
	double	x;
	double	y;
}	point_t;

typedef struct player_s
{
	// initial player angle in degrees (0 - 360) for NWES
	double		player_angle;
	// used for minimap - not for wall drawing
	// we will use the whole width of the screen for the 3D render
	double		fov;
	// initial player location in the array
	point_t		coordinates;
}	player_t;

typedef struct planes_s
{
	// minimap
	mlx_image_t *left_plane;
	// 3D render
	mlx_image_t *right_plane;
} planes_t;

typedef struct map_s
{
	//Map has always result to a square.
	// The longest line makes the square
	// All spaces (empty or any other char) outside of the walls (1) be filled with 9
	// Empty spaces inside the map fill with space (0)
	// For door 4
	char		**map;
	// In elements (sqaures)
	int			width;
	int			height;
	// struct to player
	player_t	player;
	// colors for the floor and ceiling
	uint32_t	floor_color;
	uint32_t	ceiling_color;

}	map_t;

typedef struct game_s
{
	player_t	player;
	planes_t	*game_planes;
	map_t		game_map;
}	game_t;

// MLX42 Drawing functions

//Bresenham’s line algorithm
void	draw_line(void *image, double startX, double startY, double endX, double endY, unsigned int color);
void	draw_map(mlx_image_t *image, game_t *game);
void	draw_square(mlx_image_t *image, int startX, int startY, unsigned int color);
void	put_square(mlx_image_t *image , point_t location, int32_t size, u_int32_t color);
void	set_img_background(mlx_image_t *image, int32_t color);

// Ray Casting
point_t *get_vertical_ray_coordinates(game_t *game);
point_t *get_horizontal_ray_coordinates(game_t *game);
double	get_point_distance(game_t *game, point_t *coordinates);

// Game
void	draw_rays(game_t *game);
void	draw_player(game_t *game);
void	draw_wall(game_t *game);
void	move_player(mlx_key_data_t key, void *param);


// Utils
float		deg_to_rad(int a);
int			fix_ang(int a);
u_int32_t	get_rgba(u_int32_t r, u_int32_t g, u_int32_t b, u_int32_t a);
int			load_map(char *map_str, game_t *game);
void		draw_map(mlx_image_t *image, game_t *game);

#endif
