/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 00:00:00 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int calculate_scale(t_graphics *gfx)
{
    int scale_x, scale_y, scale;
    int margin = 50;
    
    scale_x = (WINDOW_WIDTH - 2 * margin) / (gfx->map_data->cols + gfx->map_data->rows);
    scale_y = (WINDOW_HEIGHT - 2 * margin) / ((gfx->map_data->cols + gfx->map_data->rows) / 2 + 50);
    
    scale = scale_x < scale_y ? scale_x : scale_y;
    
    if (scale < 2)
        scale = 2;
    if (scale > 30)
        scale = 30;
    
    return (scale);
}

static void calculate_offset(t_graphics *gfx, int scale, int *offset_x, int *offset_y)
{
    int map_width, map_height;
    
    map_width = (gfx->map_data->cols + gfx->map_data->rows) * scale;
    map_height = (gfx->map_data->cols + gfx->map_data->rows) * scale / 2;
    
    *offset_x = (WINDOW_WIDTH - map_width) / 2 + gfx->map_data->rows * scale;
    *offset_y = (WINDOW_HEIGHT - map_height) / 2;
}

t_screen_point project_point(t_graphics *gfx, t_point *point)
{
    t_screen_point screen;
    int scale;
    int height;
    int offset_x, offset_y;
    
    scale = calculate_scale(gfx);
    
    height = scale / 2;
    if (height < 1)
        height = 1;
    
    calculate_offset(gfx, scale, &offset_x, &offset_y);
    
    screen.x = (point->x - point->y) * scale + offset_x;
    screen.y = (point->x + point->y) * scale / 2 - point->z * height + offset_y;
    
    return (screen);
}