/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/20 15:14:49 by orezek           ###   ########.fr       */
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
	int		player_angle;
	point_t	player_coordinates;
}	player_location_t;

// MLX42 Drawing functions

//Bresenham’s line algorithm
void	draw_line(void *image, double startX, double startY, double endX, double endY, unsigned int color);

void	draw_square(mlx_image_t *image, int startX, int startY, unsigned int color);

// Ray Casting
point_t *get_horizontal_ray_coordinates(player_location_t *pl, int map[18][15]);
point_t *get_vertical_ray_coordinates(player_location_t *pl, int map[18][15]);

// Game
void	draw_map(mlx_image_t *image, int arr[18][15]);
void	move_player(mlx_key_data_t key, void *param);


// Utils
float	degToRad(int a);
int		FixAng(int a);
unsigned int	get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

#endif
