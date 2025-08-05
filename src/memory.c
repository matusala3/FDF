/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 00:00:00 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_partial_map(t_point **map, int allocated_rows)
{
	int	i;

	i = 0;
	while (i < allocated_rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_graphics(t_graphics *gfx)
{
	if (gfx)
	{
		if (gfx->img_ptr)
			mlx_destroy_image(gfx->mlx_ptr, gfx->img_ptr);
		if (gfx->win_ptr)
			mlx_destroy_window(gfx->mlx_ptr, gfx->win_ptr);
		if (gfx->mlx_ptr)
		{
			mlx_destroy_display(gfx->mlx_ptr);
			free(gfx->mlx_ptr);
		}
		if (gfx->map_data)
			free_map(gfx->map_data);
		free(gfx);
	}
}

void	free_map(t_map *map_data)
{
	int	i;

	if (map_data)
	{
		if (map_data->map)
		{
			i = 0;
			while (i < map_data->rows)
			{
				free(map_data->map[i]);
				i++;
			}
			free(map_data->map);
		}
		free(map_data);
	}
}
