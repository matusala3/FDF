/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:18:52 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 19:11:00 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>

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
}	t_point;
typedef struct s_map
{
	t_point	**map;
	int		rows;
	int		cols;
}	t_map;
typedef struct s_graphics
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map_data;
}	t_graphics;

typedef struct s_spoint
{
	int	x;
	int	y;
}	t_spoint;

//assign.c
t_map		*init_map_structure(int rows, int cols);
int			allocate_map_rows(t_map *map_data, int rows, int cols);
int			process_line_data(char **split_line, t_map *map_data, int row);
int			process_single_line(char *line, t_map *map_data, int row);
int			fill_map_data(char *filename, t_map *map_data);

//color.c
int			parse_height_color(char *str, int *z_value, int *color);
int			parse_height_only(char *str, int *z_value, int *color);
int			parse_color(char *str, char *comma_pos, int *z_value, int *color);
int			get_height_color(int z);

//helper
int			handle_close(t_graphics *gfx);
int			handle_keypress(int keycode, t_graphics *gfx);

//main
int			init_graphics(t_map *map_data);
t_graphics	*allocate_graphics_struct(void);
int			setup_window_and_image(t_graphics *gfx);
void		setup_hooks_and_run(t_graphics *gfx);
int			init_graphics(t_map *map_data);

//memory
void		free_partial_map(t_point **map, int allocated_rows);
void		free_double_pointer(char **arr);
void		cleanup_graphics(t_graphics *gfx);
void		free_map(t_map *map_data);

//parse
t_map		*parse_file(char *filename);
int			get_file_dimensions(char *filename, int *rows, int *cols);
int			count_columns(char *line);
t_map		*allocate_map(int rows, int cols);

//projection
void		draw_wireframe(t_graphics *gfx);
int			calculate_scale(t_graphics *gfx);
void		calc_off(t_graphics *gfx, int scale, int *offset_x, int *offset_y);
t_spoint	project_point(t_graphics *gfx, t_point *point);

//rendering
void		put_pixel(t_graphics *gfx, int x, int y, int color);
int			calculate_steps(t_spoint p1, t_spoint p2);
void		draw_line(t_graphics *gfx, t_spoint p1, t_spoint p2, int color);

#endif