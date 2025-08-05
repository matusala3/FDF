/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 19:18:38 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_wireframe(t_graphics *gfx)
{
	int			row;
	int			col;
	t_spoint	p1;
	t_spoint	p2;

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

int	calculate_scale(t_graphics *gfx)
{
	int	scale_x;
	int	scale_y;
	int	scale;
	int	margin;

	margin = 50;
	scale_x = (WINDOW_WIDTH - 2 * margin)
		/ (gfx->map_data->cols + gfx->map_data->rows);
	scale_y = (WINDOW_HEIGHT - 2 * margin)
		/ ((gfx->map_data->cols + gfx->map_data->rows) / 2 + 50);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 2)
		scale = 2;
	if (scale > 30)
		scale = 30;
	return (scale);
}

void	calc_off(t_graphics *gfx, int scale, int *offset_x, int *offset_y)
{
	int	map_width;
	int	map_height;

	map_width = (gfx->map_data->cols + gfx->map_data->rows) * scale;
	map_height = (gfx->map_data->cols + gfx->map_data->rows) * scale / 2;
	*offset_x = (WINDOW_WIDTH - map_width) / 2 + gfx->map_data->rows * scale;
	*offset_y = (WINDOW_HEIGHT - map_height) / 2;
}

t_spoint	project_point(t_graphics *gfx, t_point *point)
{
	t_spoint	screen;
	int			scale;
	int			height;
	int			offset_x;
	int			offset_y;

	scale = calculate_scale(gfx);
	height = scale / 2;
	if (height < 1)
		height = 1;
	calc_off(gfx, scale, &offset_x, &offset_y);
	screen.x = (point->x - point->y) * scale + offset_x;
	screen.y = (point->x + point->y) * scale / 2 - point->z * height + offset_y;
	return (screen);
}
