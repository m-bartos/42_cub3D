/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:46:56 by orezek            #+#    #+#             */
/*   Updated: 2024/06/17 23:05:48 by orezek           ###   ########.fr       */
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
// MLX42 Drawing functions

//Bresenham’s line algorithm
void	draw_line(void *image, int beginX, int beginY, int endX, int endY, unsigned int color);

void	draw_square(mlx_image_t *image, int startX, int startY, unsigned int color);

#endif
