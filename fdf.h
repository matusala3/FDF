/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:18:52 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/01 21:25:29 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <fcntl.h>
#include <math.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "FDF - Wireframe Model"

# define MAP_SCALE 40
# define MAP_HEIGHT 5

typedef struct s_point
{
    int	x;
	int	y;
	int	z;
	int	color;
} t_point;
typedef struct s_map
{
	t_point	**map;
	int		rows;
	int		cols;
}	t_map;
typedef struct s_graphics
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    t_map   *map_data;
}	t_graphics;

typedef struct s_screen_point
{
    int x;
    int y;
} t_screen_point;

//parse
t_map *parse_file(char *filename);
t_map *allocate_map(int rows, int cols);
int get_file_dimensions(char *filename, int *rows, int *cols);
int fill_map_data(char *filename, t_map *map_data);
int get_height_color(int z);

//helper
void free_partial_map(t_point **map, int allocated_rows);
int count_columns(char *line);
void free_double_pointer(char **arr);

// Function prototype:
int init_graphics(t_map *map_data);
void cleanup_graphics(t_graphics *gfx);
int handle_keypress(int keycode, t_graphics *gfx);
int handle_close(t_graphics *gfx);
void free_map(t_map *map_data);

//main
int init_graphics(t_map *map_data);

//draw
void draw_wireframe(t_graphics *gfx);
void draw_line(t_graphics *gfx, t_screen_point p1, t_screen_point p2, int color);
t_screen_point project_point(t_graphics *gfx, t_point *point);
void put_pixel(t_graphics *gfx, int x, int y, int color);

#endif