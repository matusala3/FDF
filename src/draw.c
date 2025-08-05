/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:26:24 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 14:02:54 by magebreh         ###   ########.fr       */
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

