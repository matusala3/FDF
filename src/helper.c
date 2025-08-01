/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:19:18 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/31 20:27:23 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int count_columns(char *line)
{
    char **split;
    int count;
    
	split = ft_split(line, ' ');
	count = 0;
    while (split[count])
        count++;
    free_double_pointer(split);
    return (count);
};

void free_partial_map(t_point **map, int allocated_rows)
{
    int i = 0;
    while (i < allocated_rows)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_double_pointer(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void cleanup_graphics(t_graphics *gfx)
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

int handle_keypress(int keycode, t_graphics *gfx)
{
    ft_printf("Key pressed: %d\n", keycode);
    
    if (keycode == 65307)
    {
        ft_printf("ESC pressed - exiting\n");
        cleanup_graphics(gfx);
        exit(0);
    }
    
    return (0);
}

int handle_close(t_graphics *gfx)
{
    ft_printf("Window close button pressed\n");
    cleanup_graphics(gfx);
    exit(0);
    return (0);
}

void free_map(t_map *map_data)
{
    if (map_data)
    {
        if (map_data->map)
        {
            int i = 0;
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
