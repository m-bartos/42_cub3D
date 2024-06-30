/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/30 16:12:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

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
# define FLOOR 0x654321
# define CEILING 0x654321
# define WALL 0x00ff00
# define RAY 0x000000
# define PLAYER 0x00ff00
# define L_BACKGROUND 0x000000
# define R_BACKGROUND 0x000000
# define MINI_WALL 0xff0000
# define MINI_FLOOR 0xffffff

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

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	double		angle;
	double		fov;
	t_point		coordinates;
}	t_player;

typedef struct s_planes
{
	mlx_image_t	*mini_plane;
	mlx_image_t	*game_plane;
}	t_planes;

typedef struct s_textures
{
	mlx_texture_t	*angle_0;
	mlx_texture_t	*angle_90;
	mlx_texture_t	*angle_180;
	mlx_texture_t	*angle_270;
}	t_textures;

typedef struct s_map
{
	char		**temp_arr;
	char		**map;
	int			width;
	int			height;
	int			square_size;
	t_player	*player;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_textures	*txts;
}	t_map;

typedef struct s_game
{
	t_player	*player;
	t_planes	*planes;
	t_map		*map;
}	t_game;

// Draw ray
typedef struct s_draw_ray
{
	t_planes	*planes;
	t_point		*hrc;
	t_point		*vrc;
	double		fov;
	double		pa;
	double		h_distance;
	double		v_distance;
	int			r;

}	t_draw_ray;

// Draw Wall
typedef struct s_draw_wall
{
	t_point			*hrc;
	t_point			*vrc;
	t_planes		*planes;
	double			corrected_distance;
	double			h_distance;
	double			v_distance;
	double			fov;
	double			pa;
	double			angle_increment;
	int				screen_height;
	int				screen_width;
	double			max_wall_height;
	double			line_height;
	double			old_line_height;
	double			line_offset;
	int				ray_x_position;
	mlx_texture_t	*wall;
	double			texture_x;
	int				texture_x_index;
	int				texture_y_index;
	double			texture_y_ratio;
	unsigned int	color;
	int				ray;
	int				pixel;
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
	t_game		*game;
	t_player	*player;
	double		pdx;
	double		pdy;
}	t_move_player;

// Get horizontal ray intersection
typedef struct s_hrc
{
	t_point	*hor_ray;
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
	t_point	*ver_ray;
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
	int	err;
	int	e2;
}	t_draw_line;

// MLX42 Drawing functions

//Bresenham’s line algorithm
void			draw_line(mlx_image_t *image, t_point start, t_point end,
					uint32_t color);
void			draw_map(mlx_image_t *image, t_game *game);
void			draw_square(mlx_image_t *image, int startX, int startY,
					unsigned int color);
void			put_square(mlx_image_t *image, t_point location,
					int32_t size, u_int32_t color);
void			set_img_background(mlx_image_t *image, int32_t color);

// Ray Casting
t_point			*get_vertical_ray_coordinates(t_game *game);
t_point			*get_horizontal_ray_coordinates(t_game *game);
double			get_point_distance(t_game *game, t_point *coordinates);

// Game
void			draw_rays(t_game *game);
void			draw_player(t_game *game);
void			draw_wall(t_game *game);

// Player move
void			move_player(mlx_key_data_t key, void *param);
void			step_right(t_move_player *p);
void			step_left(t_move_player *p);
void			move_forward(t_move_player *p);
void			move_backward(t_move_player *p);
void			turn_left(t_move_player *p);
void			turn_right(t_move_player *p);
bool			no_wall(t_game *game, double step_x, double step_y);

// Utils
double			deg_to_rad(double a);
double			fix_ang(double a);
u_int32_t		get_rgba(u_int32_t r, u_int32_t g, u_int32_t b, u_int32_t a);
int				load_map(char *map_str, t_game *game);
void			draw_map(mlx_image_t *image, t_game *game);
uint32_t		get_pixel_color(mlx_texture_t *texture,
					int y_height, int x_width);
mlx_texture_t	*get_texture(t_game *game,
					double h_distance, double v_distance);

// Parser
int				is_valid_map_line(char *line);
void			check_valid_map_chars(char **map);
void			set_map_size(t_map *map);
void			change_player_coordinates_format(t_player *player);
void			clean_map(t_map *map);
void			init_map(t_map *map);
int				max_line_width(char **map_array);
void			delete_last_empty_lines_in_arr(char **file_content);
void			check_suffix(char *str);
char			**add_borders_fill_spaces(char **map_array);
char			**load_file_to_array(int fd);
char			**get_file_array(char *map_name);
char			**ft_arrdup(char **arr);
void			get_player_pos(t_map *map);
void			replace_start_pos_in_map(char **map);
void			map_flood_fill(char **map_array, size_t y, size_t x);
void			check_start_possitions(char **map_array);
int				is_empty_line(char *line);
char			**seperate_map(char **file_content);
char			*delete_extra_spaces(char *str);
mlx_texture_t	*load_png_from_path(char *path);
void			get_textures(t_map *map, char **file_arr);
void			check_valid_color_line(char *str);
int				get_color_from_str(char *str);
void			get_colors(t_map *map, char **file_arr);
void			check_textures(t_map *map);
void			check_colors(t_map *map);
void			fill_map_struct(t_map *map, char *str);

// errors.c
void			error_argc(int argc);

// get_map.c
void			fill_map_struct(t_map *map, char *str);

#endif
