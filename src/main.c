/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:19:53 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/01 19:00:48 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int main(int argc, char **argv)
{
    t_map *map_data;
    
    if(argc != 2)
    {
        ft_printf("Usage: ./fdf <filename.fdf>\n");
        return (1);
    }
    map_data = parse_file(argv[1]);
    if (!map_data)
    {
        ft_printf("Error: Failed to parse file\n");
        return (1);
    }
	if (!init_graphics(map_data))
    {
        ft_printf("Error: Failed to initialize graphics\n");
        free_map(map_data);
        return (1);
    }
    return (0);
}

static t_graphics	*allocate_graphics_struct(void)
{
	t_graphics	*gfx;

	gfx = malloc(sizeof(t_graphics));
	if (!gfx)
		return (NULL);
	gfx->mlx_ptr = mlx_init();
	if (!gfx->mlx_ptr)
	{
		free(gfx);
		return (NULL);
	}
	return (gfx);
}

static int	setup_window_and_image(t_graphics *gfx)
{
	gfx->win_ptr = mlx_new_window(gfx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!gfx->win_ptr)
		return (0);
	gfx->img_ptr = mlx_new_image(gfx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!gfx->img_ptr)
	{
		mlx_destroy_window(gfx->mlx_ptr, gfx->win_ptr);
		mlx_destroy_display(gfx->mlx_ptr);
		return (0);
	}
	gfx->img_data = mlx_get_data_addr(gfx->img_ptr, &gfx->bits_per_pixel, &gfx->line_length, &gfx->endian);
	return (1);
}

static void	setup_hooks_and_run(t_graphics *gfx)
{
	mlx_hook(gfx->win_ptr, 2, 1L<<0, handle_keypress, gfx);
	mlx_hook(gfx->win_ptr, 17, 1L<<17, handle_close, gfx);
	draw_wireframe(gfx);
	mlx_loop(gfx->mlx_ptr);
}

int init_graphics(t_map *map_data)
{
	t_graphics	*gfx;

	gfx = allocate_graphics_struct();
	if (!gfx)
		return (0);
	if (!setup_window_and_image(gfx))
	{
		free(gfx);
		return (0);
	}
	gfx->map_data = map_data;
	setup_hooks_and_run(gfx);
	return (1);
}

