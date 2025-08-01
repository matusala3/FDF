/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:26:24 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/01 21:25:08 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void draw_wireframe(t_graphics *gfx)
{
	int row;
	int col;
	t_screen_point p1;
	t_screen_point p2;

	row = 0;
	while (row < gfx->map_data->rows)
	{
		col = 0;
		while (col < gfx->map_data->cols)
		{
			p1 = project_point(gfx, &gfx->map_data->map[row][col]);
			if (col + 1 < gfx->map_data->cols)
			{
				p2 = project_point(gfx, &gfx->map_data->map[row][col + 1]);
				draw_line(gfx, p1, p2, gfx->map_data->map[row][col].color);
			}
			if (row + 1 < gfx->map_data->rows)
			{
				p2 = project_point(gfx, &gfx->map_data->map[row + 1][col]);
				draw_line(gfx, p1, p2, gfx->map_data->map[row][col].color);
			}
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(gfx->mlx_ptr, gfx->win_ptr, gfx->img_ptr, 0, 0);	
}

void draw_line(t_graphics *gfx, t_screen_point p1, t_screen_point p2, int color)
{
    int abs_dx;
    int abs_dy;
    int steps;
    int x; 
    int y;
    int i;
    
    if (p2.x - p1.x < 0)
        abs_dx = -(p2.x - p1.x); 
    else
        abs_dx = p2.x - p1.x;
    if (p2.y - p1.y < 0)
        abs_dy = -(p2.y - p1.y); 
    else
        abs_dy = p2.y - p1.y;
    if (abs_dx > abs_dy)
        steps = abs_dx;
    else
        steps = abs_dy;
    if (steps == 0)
    {
        put_pixel(gfx, p1.x, p1.y, color);
        return;
    }
    i = 0;
    while (i <= steps)
    {
        x = p1.x + ((p2.x - p1.x) * i) / steps;
        y = p1.y + ((p2.y - p1.y) * i) / steps;
        put_pixel(gfx, x, y, color);
        i++;
    }
}

t_screen_point project_point(t_graphics *gfx, t_point *point)
{
    t_screen_point screen;
    int scale = 20;
    int height = 20;

    int map_width = (gfx->map_data->cols + gfx->map_data->rows) * scale;
    int map_height = (gfx->map_data->cols + gfx->map_data->rows) * scale;

    int offset_x = (WINDOW_WIDTH - map_width) / 2;
    int offset_y = (WINDOW_HEIGHT - map_height) / 2;
    
    screen.x = (point->x - point->y) * scale + offset_x;
    screen.y = (point->x + point->y) * scale - point->z * height + offset_y;
    
    return (screen);
}

void put_pixel(t_graphics *gfx, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = gfx->img_data + (y * gfx->line_length + x * (gfx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
