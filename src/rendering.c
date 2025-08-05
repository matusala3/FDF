/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 00:00:00 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void put_pixel(t_graphics *gfx, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = gfx->img_data + (y * gfx->line_length + x * (gfx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static int calculate_steps(t_screen_point p1, t_screen_point p2)
{
    int abs_dx, abs_dy;
    
    if (p2.x - p1.x < 0)
        abs_dx = -(p2.x - p1.x); 
    else
        abs_dx = p2.x - p1.x;
    if (p2.y - p1.y < 0)
        abs_dy = -(p2.y - p1.y); 
    else
        abs_dy = p2.y - p1.y;
    
    if (abs_dx > abs_dy)
        return (abs_dx);
    else
        return (abs_dy);
}

void draw_line(t_graphics *gfx, t_screen_point p1, t_screen_point p2, int color)
{
    int steps;
    int x; 
    int y;
    int i;
    
    steps = calculate_steps(p1, p2);
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