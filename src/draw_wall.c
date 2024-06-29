/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 15:49:42 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"



typedef struct s_draw_wall
{
	point_t		*hrc;
	point_t		*vrc;
	planes_t	*game_planes;
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

void	init_draw_wall(game_t *game, t_draw_wall *w)
{
	*w = (t_draw_wall){0};
	// get screen size
	w->screen_height = game->game_planes->game_plane->height;
	w->screen_width = game->game_planes->game_plane->width;
	// set initial player angle
	w->pa = game->player->player_angle;
	w->game_planes = game->game_planes;
	w->fov = game->player->fov;
	// Angle increment
	w->angle_increment = w->fov / w->screen_width;
}

void	draw_vertical_lines(game_t *game, t_draw_wall *w)
{
	// floor
	draw_line(w->game_planes->game_plane,
		w->ray_x_position, WINDOW_HEIGHT - 1,
		w->ray_x_position, WINDOW_HEIGHT - 1 - round(w->line_offset),
		game->game_map->floor_color);
	// wall
	if (NO_TEXTURES)
		draw_line(w->game_planes->game_plane,
		w->ray_x_position, w->line_offset,
		w->ray_x_position, round (w->line_offset + w->line_height), WALL);
	// ceiling
	draw_line(w->game_planes->game_plane,
		w->ray_x_position, 0, w->ray_x_position,
		round(w->line_offset),
		game->game_map->ceiling_color);
}

void	calculate_line_lenghts(t_draw_wall *w)
{
	w->max_wall_height = w->screen_height;
	w->line_height = (SQUARE_SIZE * w->max_wall_height) / w->corrected_distance;
	w->old_line_height = w->line_height;
	if (w->line_height > w->screen_height)
		w->line_height = w->screen_height;
	w->line_offset = (w->screen_height / 2) - (w->line_height / 2);
	w->ray_x_position = WINDOW_WIDTH - w->ray - 1;
}

void	draw_wall(game_t *game)
{
		t_draw_wall		w;

		init_draw_wall(game, &w);

		while (w.ray < w.screen_width)
		{
			// calculate agle for the 60 fov
			game->player->player_angle = fix_ang((w.pa - w.fov / 2) + w.ray * w.angle_increment);
			// cast ray and get horizontal coordiantes
			w.hrc = get_horizontal_ray_coordinates(game);
			// cast ray and get vertical coordinates
			w.vrc = get_vertical_ray_coordinates(game);
			// get horizontal distance between the two points
			w.h_distance = get_point_distance(game, w.hrc);

			// get vertical distance between the two points
			w.v_distance = get_point_distance(game, w.vrc);
			// choose shorter distance
			if (w.v_distance < w.h_distance)
				w.corrected_distance = w.v_distance * cos(deg_to_rad(game->player->player_angle - w.pa));
			else
				w.corrected_distance = w.h_distance * cos(deg_to_rad(game->player->player_angle - w.pa));
			calculate_line_lenghts(&w);
			// Draw Textures
			w.wall = get_texture(game, w.h_distance, w.v_distance);
			if (w.v_distance < w.h_distance)
			{
				w.texture_x = w.vrc->y - floor(w.vrc->y / SQUARE_SIZE) * SQUARE_SIZE;
			}
			else
			{
				w.texture_x = w.hrc->x - floor(w.hrc->x / SQUARE_SIZE) * SQUARE_SIZE;
			}
			w.texture_x_index = (int)w.texture_x * w.wall->width / SQUARE_SIZE;
			// Draw the wall slice with texture mapping
			w.pixel = 0;
        	while (w.pixel < w.line_height)
			{
				w.texture_y_ratio = w.wall->height / w.old_line_height; // it determines the ratio between unit of the line
				if (w.old_line_height > w.screen_height)
					w.texture_y_index = (int)((w.pixel + (w.old_line_height - w.screen_height) / 2) * w.texture_y_ratio); // calculates y position of the pixel
				else
					w.texture_y_index = (int)(w.texture_y_ratio * w.pixel); // calculates y position of the pixel
				// test the pixel color from the coordinates
				w.color = get_pixel_color(w.wall, w.texture_y_index, w.texture_x_index);
				mlx_put_pixel(w.game_planes->game_plane, w.ray_x_position, (int)(w.line_offset + w.pixel), w.color);
				w.pixel++;
			}
			// End of textures
			draw_vertical_lines(game, &w);
			w.ray++;
		}
		game->player->player_angle = w.pa;
}
