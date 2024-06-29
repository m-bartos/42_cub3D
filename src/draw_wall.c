/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:44:30 by orezek            #+#    #+#             */
/*   Updated: 2024/06/29 17:02:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	init_draw_wall(game_t *game, t_draw_wall *w)
{
	*w = (t_draw_wall){0};
	w->screen_height = game->planes->game_plane->height;
	w->screen_width = game->planes->game_plane->width;
	w->pa = game->player->angle;
	w->planes = game->planes;
	w->fov = game->player->fov;
	w->angle_increment = w->fov / w->screen_width;
}

static void	draw_vertical_lines(game_t *game, t_draw_wall *w)
{
	draw_line(w->planes->game_plane,
		w->ray_x_position, WINDOW_HEIGHT - 1,
		w->ray_x_position, WINDOW_HEIGHT - 1 - round(w->line_offset),
		game->map->floor_color);
	if (NO_TEXTURES)
		draw_line(w->planes->game_plane,
			w->ray_x_position, w->line_offset,
			w->ray_x_position, round (w->line_offset + w->line_height), WALL);
	draw_line(w->planes->game_plane,
		w->ray_x_position, 0, w->ray_x_position,
		round(w->line_offset),
		game->map->ceiling_color);
}

static void	calculate_line_lenghts(t_draw_wall *w)
{
	w->max_wall_height = w->screen_height;
	w->line_height = (SQUARE_SIZE * w->max_wall_height) / w->corrected_distance;
	w->old_line_height = w->line_height;
	if (w->line_height > w->screen_height)
		w->line_height = w->screen_height;
	w->line_offset = (w->screen_height / 2) - (w->line_height / 2);
	w->ray_x_position = WINDOW_WIDTH - w->ray - 1;
}

static void	draw_textures(game_t *game, t_draw_wall *w)
{
	w->wall = get_texture(game, w->h_distance, w->v_distance);
	if (w->v_distance < w->h_distance)
		w->texture_x = w->vrc->y - floor(w->vrc->y / SQUARE_SIZE) * SQUARE_SIZE;
	else
		w->texture_x = w->hrc->x - floor(w->hrc->x / SQUARE_SIZE) * SQUARE_SIZE;
	w->texture_x_index = (int)w->texture_x * w->wall->width / SQUARE_SIZE;
	w->pixel = 0;
	while (w->pixel < w->line_height)
	{
		w->texture_y_ratio = w->wall->height / w->old_line_height;
		if (w->old_line_height > w->screen_height)
			w->texture_y_index = (int)((w->pixel
						+ (w->old_line_height - w->screen_height)
						/ 2) * w->texture_y_ratio);
		else
			w->texture_y_index = (int)(w->texture_y_ratio * w->pixel);
		w->color = get_pixel_color(w->wall, w->texture_y_index,
				w->texture_x_index);
		mlx_put_pixel(w->planes->game_plane, w->ray_x_position,
			(int)(w->line_offset + w->pixel), w->color);
		w->pixel++;
	}
}

void	draw_wall(game_t *game)
{
	t_draw_wall		w;

	init_draw_wall(game, &w);
	while (w.ray < w.screen_width)
	{
		game->player->angle = fix_ang((w.pa - w.fov / 2)
				+ w.ray * w.angle_increment);
		w.hrc = get_horizontal_ray_coordinates(game);
		w.vrc = get_vertical_ray_coordinates(game);
		w.h_distance = get_point_distance(game, w.hrc);
		w.v_distance = get_point_distance(game, w.vrc);
		if (w.v_distance < w.h_distance)
			w.corrected_distance = w.v_distance
				* cos(deg_to_rad(game->player->angle - w.pa));
		else
			w.corrected_distance = w.h_distance
				* cos(deg_to_rad(game->player->angle - w.pa));
		calculate_line_lenghts(&w);
		draw_textures(game, &w);
		draw_vertical_lines(game, &w);
		w.ray++;
	}
	game->player->angle = w.pa;
}
