/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 14:02:42 by orezek           ###   ########.fr       */
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
# include <string.h>
# include <fcntl.h>

// Size of the map - not used now
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
// Will be determined at load time (based on map size)
# define SQUARE_SIZE 64
# define NO_TEXTURES false

// Define the pixel change when key is pressed
# define KEY_PRESS 5
// Length of the so called player on minimap
# define PLAYER_LENGTH 100

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


// Map Constants
# define M_WALL '1'
# define M_FLOOR '0'
# define M_OUT '9'
# define M_DOOR '4'

// Cardinal directions within Unit circle
# define EAST_D 270.0
# define WEST_D 90.0
# define NORTH_D 0.0
# define SOUTH_D 180.0

// Paths to PNG files for textures
# define WEST "./textures/west.png"
# define EAST "./textures/east.png"
# define NORTH "./textures/north.png"
# define SOUTH "./textures/south.png"
# define B_WALL "./textures/brick_wall.png"

typedef struct point_s
{
	double	x;
	double	y;
}	point_t;

typedef struct player_s
{
	// initial player angle in degrees (0 - 360) for NWES
	double		angle;
	// used for minimap - not for wall drawing
	// we will use the whole width of the screen for the 3D render
	double		fov;
	// initial player location in the array
	point_t		coordinates;
}	player_t;

typedef struct planes_s
{
	// minimap
	mlx_image_t *mini_plane;
	// 3D render
	mlx_image_t *game_plane;
}	planes_t;

// typedef struct png_paths_s
// {
// 	char	*no;
// 	char	*so;
// 	char	*we;
// 	char	*ea;
// }	png_paths_t;

// typedef struct textures_s
// {
// 	mlx_texture_t	*we;
// 	mlx_texture_t	*ea;
// 	mlx_texture_t	*no;
// 	mlx_texture_t	*so;
// }	textures_t;

typedef struct textures_s
{
	mlx_texture_t *angle_0;
	mlx_texture_t *angle_90;
	mlx_texture_t *angle_180;
	mlx_texture_t *angle_270;
}	textures_t;

typedef struct map_s
{
	//Map has always result to a square or a rectangle.
	// The longest line makes the square
	// All spaces (empty or any other char) outside of the walls (1) be filled with (9)
	// Empty spaces inside the map fill with space (0)
	// For door (4)
	char		**temp_arr;
	char		**map;
	// In elements (sqaures)
	int			width;
	int			height;
	int			square_size;
	// struct to player
	player_t	*player;
	// colors for the floor and ceiling
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	textures_t	*txts;
	// png_paths_t	png_paths;
	//textures_t	game_textures;


}	map_t;

typedef struct game_s
{
	player_t	*player;
	planes_t	*planes;
	map_t		*map;
}	game_t;

// Function structs

// Draw ray
typedef struct s_draw_ray
{
	planes_t	*planes;
	point_t		*hrc;
	point_t		*vrc;
	double		fov;
	double		pa;
	double		h_distance;
	double		v_distance;
	int			r;

}	t_draw_ray;

// Draw Wall
typedef struct s_draw_wall
{
	point_t		*hrc;
	point_t		*vrc;
	planes_t	*planes;
	double		corrected_distance;
	double		h_distance;
	double		v_distance;
	double		fov;
	double		pa;
	double		angle_increment;
	int			screen_height;
	int			screen_width;
	double		max_wall_height;
	double		line_height;
	double 		old_line_height;
	double 		line_offset;
	int			ray_x_position;
	mlx_texture_t	*wall;
	double		texture_x;
	int			texture_x_index;
	int			texture_y_index;
	double		texture_y_ratio;
	unsigned int	color;
	int	ray;
	int	pixel;
}	t_draw_wall;

// Draw_map
typedef struct s_draw_map
{
	char	**arr;
	int		s_size;
	int		y_map_size;
	int		x_map_size;
	int		x;
	int		y;
}	t_draw_map;

// Move player
typedef struct s_move_player
{
	game_t		*game;
	player_t	*player;
	double		pdx;
	double		pdy;

} t_move_player;

// Get horizontal ray intersection
typedef struct s_hrc
{
	point_t *hor_ray;
	int		map_x;
	int		map_y;
	int		map_max_size;
	double	pa;
	double	px;
	double	py;
	char	**map;
	int		mx;
	int		my;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	a_tan;
}	t_hrc;

typedef struct s_vrc
{
	point_t *ver_ray;
	int		map_x;
	int		map_y;
	int		map_max_size;
	double	pa;
	double	px;
	double	py;
	char	**map;
	int		mx;
	int		my;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	n_tan;
}	t_vrc;

// Draw line
typedef struct s_draw_line
{
	int	sxi;
	int	syi;
	int	exi;
	int	eyi;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int err;
	int e2;

}	t_draw_line;

// MLX42 Drawing functions

//Bresenham’s line algorithm
void	draw_line(mlx_image_t *image, point_t start, point_t end, uint32_t color);
void	draw_map(mlx_image_t *image, game_t *game);
void	draw_square(mlx_image_t *image, int startX, int startY, unsigned int color);
void	put_square(mlx_image_t *image , point_t location, int32_t size, u_int32_t color);
void	set_img_background(mlx_image_t *image, int32_t color);

// Ray Casting
point_t	*get_vertical_ray_coordinates(game_t *game);
point_t	*get_horizontal_ray_coordinates(game_t *game);
double	get_point_distance(game_t *game, point_t *coordinates);

// Game
void	draw_rays(game_t *game);
void	draw_player(game_t *game);
void	draw_wall(game_t *game);

// Player move
void	move_player(mlx_key_data_t key, void *param);
void	step_right(t_move_player *p);
void	step_left(t_move_player *p);
void	move_forward(t_move_player *p);
void	move_backward(t_move_player *p);
void	turn_left(t_move_player *p);
void	turn_right(t_move_player *p);
bool	no_wall(game_t *game, double step_x, double step_y);

// Utils
double		deg_to_rad(double a);
double		fix_ang(double a);
u_int32_t	get_rgba(u_int32_t r, u_int32_t g, u_int32_t b, u_int32_t a);
int			load_map(char *map_str, game_t *game);
void		draw_map(mlx_image_t *image, game_t *game);
uint32_t	get_pixel_color(mlx_texture_t *texture, int y_height, int x_width);
mlx_texture_t	*get_texture(game_t *game, double h_distance, double v_distance);

// Parser
int		is_valid_map_line(char *line);
void	check_valid_map_chars(char **map);
void	set_map_size(map_t *map);
void	change_player_coordinates_format(player_t *player);
void	clean_map(map_t *map);
void	init_map(map_t *map);
int		max_line_width(char **map_array);
void	delete_last_empty_lines_in_arr(char **file_content);
void	check_suffix(char *str);
char	**add_borders_fill_spaces(char **map_array);
char	**load_file_to_array(int fd);
char	**get_file_array(char *map_name);
char	**ft_arrdup(char **arr);
void	get_player_pos(map_t *map);
void	replace_start_pos_in_map(char **map);
void	map_flood_fill(char **map_array, size_t y, size_t x);
void	check_start_possitions(char **map_array);
int		is_empty_line(char *line);
char	**seperate_map(char **file_content);
char	*delete_extra_spaces(char *str);
mlx_texture_t	*load_png_from_path(char *path);
void	get_textures(map_t *map, char **file_arr);
void	check_valid_color_line(char *str);
int		get_color_from_str(char *str);
void	get_colors(map_t *map, char **file_arr);
void	check_textures(map_t *map);
void	check_colors(map_t *map);
void	fill_map_struct(map_t *map, char *str);


// errors.c
void	error_argc(int argc);

// get_map.c
void	fill_map_struct(map_t *map, char *str);

#endif
