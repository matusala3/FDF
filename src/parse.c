/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:36:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 13:02:01 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_map *parse_file(char *filename)
{
    int		rows; 
	int		cols;
	int		i;
    t_map	*map_data;
    
    if (!get_file_dimensions(filename, &rows, &cols))
        return (NULL);
    map_data = allocate_map(rows, cols);
    if (!map_data)
        return (NULL);
    if (!fill_map_data(filename, map_data))
    {
        i = 0;
		while (i < rows)
		{
			free(map_data->map[i]);
			i++;
		}
		free(map_data->map);
		free(map_data);
		return (NULL);
    }
    return (map_data);
}

int get_file_dimensions(char *filename, int *rows, int *cols)
{
    int fd;
    char *line;
    int current_cols;
    
	fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    *rows = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        current_cols = count_columns(line);
        
        if (*rows == 0)
            *cols = current_cols;
        else if (current_cols != *cols)
        {
            free(line);
            close(fd);
            return (0);
        }
        (*rows)++;
        free(line);
    }
    close(fd);
    return (1);
}

static t_map	*init_map_structure(int rows, int cols)
{
	t_map	*map_data;

	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->rows = rows;
	map_data->cols = cols;
	map_data->map = malloc(rows * sizeof(t_point *));
	if (!map_data->map)
	{
		free(map_data);
		return (NULL);
	}
	return (map_data);
}

static int	allocate_map_rows(t_map *map_data, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		map_data->map[i] = malloc(cols * sizeof(t_point));
		if (!map_data->map[i])
		{
			free_partial_map(map_data->map, i);
			free(map_data);
			return (0);
		}
		i++;
	}
	return (1);
}

t_map *allocate_map(int rows, int cols)
{
	t_map	*map_data;

	map_data = init_map_structure(rows, cols);
	if (!map_data)
		return (NULL);
	if (!allocate_map_rows(map_data, rows, cols))
		return (NULL);
	return (map_data);
}

static int	process_line_data(char **split_line, t_map *map_data, int row)
{
	int	col;
	int	z_value;
	int	color;

	col = 0;
	while (split_line[col] != NULL)
	{
		if (!parse_height_color(split_line[col], &z_value, &color))
			return (0);
		map_data->map[row][col].x = col;
		map_data->map[row][col].y = row;
		map_data->map[row][col].z = z_value;
		map_data->map[row][col].color = color;
		col++;
	}
	return (1);
}

static int	process_single_line(char *line, t_map *map_data, int row)
{
	char	**split_line;
	int		result;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (0);
	result = process_line_data(split_line, map_data, row);
	if (!result)
	{
		free_double_pointer(split_line);
		return (0);
	}
	free_double_pointer(split_line);
	return (1);
}

int fill_map_data(char *filename, t_map *map_data)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	row = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!process_single_line(line, map_data, row))
		{
			free(line);
			close(fd);
			return (0);
		}
		row++;
		free(line);
	}
	close(fd);
	return (1);
}

int count_columns(char *line)
{
    char **split;
    int count;
    
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	count = 0;
    while (split[count])
        count++;
    free_double_pointer(split);
    return (count);
}
