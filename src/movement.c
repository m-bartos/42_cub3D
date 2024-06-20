/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:53 by orezek            #+#    #+#             */
/*   Updated: 2024/06/20 16:22:08 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(mlx_key_data_t key, void *param)
{
	// starting player coordinates
	static double x = 600;
	static double y = 600;
	static double pdx;
	static double pdy;
	static int pa = 90;

	int startX = 0;
	int startY = 0;

	int endX = 0;
	int endY = 0;

	pdx = cos(degToRad(pa));
	pdy = sin(degToRad(pa));
	unsigned int color = get_rgba(0, 255, 0, 255);
	mlx_image_t *left_pane = (mlx_image_t *) param;
	//clear_square(background, x, y);
	startX = round(x);
	startY = round(y);
	endX = round(x+pdx*100);
	endY = round(y+pdy*100);


	// clean line
	//draw_line(background, startX, startY, endX, endY, get_rgba(255, 255, 255, 255));


////////////////////////////////////////////////////////////////////////////////
// Testing cleaning initial or previous screen - it works
	int l_color = get_rgba(0, 10, 139, 255);
	for (int x = 0; x < 960; x++)
	{
		// height
		for (int y = 0; y < 1200; y++)
		{
			//printf("%d\n", x);
			mlx_put_pixel(left_pane, x, y, l_color);
		}
	}

	int map[18][15] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
	{1,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	draw_map(left_pane, map);
////////////////////////////////////////////////////////////////////////////////
	if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_D)
		x += 5;
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_A)
		x -= 5;
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_W)
	{
		x += pdx * 5;
		y += pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_S)
	{
		x-= pdx * 5;
		y-= pdy * 5;
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_LEFT)
	{
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = sin(degToRad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_RIGHT)
	{
		pa += 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = sin(degToRad(pa));
	}
	else if ((key.action == MLX_PRESS  || key.action == MLX_REPEAT) && key.key == MLX_KEY_X)
	{
		printf("You pressed X\n");
	}

	for (int r = 0; r < 360; r++)
	{
		////////////////////////////////////////////////////////
		// Ray casting rendering
		// Ray Casting
		double h_distance = 0;
		double v_distance = 0;

		point_t *hrc;
		point_t *vrc;
		player_location_t pl;
		pl.player_angle = FixAng((pa - 360 / 2) + r);
		pl.player_angle+=1;
		pl.player_coordinates.x = startX;
		pl.player_coordinates.y = startY;
		hrc = get_horizontal_ray_coordinates(&pl, map);
		vrc = get_vertical_ray_coordinates(&pl, map);

		printf("Func - Horizontal: Rx: %f, Ry: %f\n", hrc->x,hrc->y);
		printf("Func - Vertical: Rx: %f, Ry: %f\n", vrc->x, vrc->y);

		h_distance = sqrt((hrc->x - pl.player_coordinates.x) * (hrc->x - pl.player_coordinates.x) + (hrc->y - pl.player_coordinates.y) * (hrc->y - pl.player_coordinates.y));
		v_distance = sqrt((vrc->x - pl.player_coordinates.x) * (vrc->x - pl.player_coordinates.x) + (vrc->y - pl.player_coordinates.y) * (vrc->y - pl.player_coordinates.y));

		printf("Horizontal Distance: %f\n", h_distance);
		printf("Vertical Distance: %f\n", v_distance);
		int ppp_color = get_rgba(0, 0, 0, 255);
		if (v_distance < h_distance)
		{
			draw_line(left_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
			//draw_line(right_pane, pl.player_coordinates.x, pl.player_coordinates.y, vrc->x, vrc->y, ppp_color);
		}
		else
		{
			draw_line(left_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
			//draw_line(right_pane, pl.player_coordinates.x, pl.player_coordinates.y, hrc->x, hrc->y, ppp_color);
		}
	// End of Ray Casting
		printf("R: %d\n", r);
	}

	/////////////////////////////////////////////////////////////////////
	startX = round(x);
	startY = round(y);
	endX = round(x+pdx*100);
	endY = round(y+pdy*100);
	//printf("End Points: PDX: %f PDY: %f\n", x+pdx, y+pdy);
	draw_line(left_pane, startX, startY, endX, endY, color);
}
