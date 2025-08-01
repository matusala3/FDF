/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:36:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/01 21:17:55 by magebreh         ###   ########.fr       */
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
        return (1);
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

t_map *allocate_map(int rows, int cols)
{
    t_map	*map_data;
    int		i;

	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (NULL);
	map_data->rows = rows;
	map_data->cols = cols;
	map_data->map = malloc(rows *sizeof(t_point *));
    if (!map_data->map)
    {
        free(map_data);
        return (NULL);
    }
    i = 0;
    while (i < rows)
    {
        map_data->map[i] = malloc(cols *sizeof(t_point));
        if(!map_data->map[i])
        {
            free_partial_map(map_data->map, i);
            free(map_data);
            return (NULL);
        }
        i++;
    }
    return (map_data);
}

int fill_map_data(char *filename, t_map *map_data)
{
    int fd;
    char *line;
    char **split_line;
    int row;
    int col;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        split_line = ft_split(line, ' ');
        col = 0;
        while (split_line[col] != NULL)
        {
            int z_value = ft_atoi(split_line[col]);
            map_data->map[row][col].x = col;
            map_data->map[row][col].y = row;
            map_data->map[row][col].z = z_value;
            map_data->map[row][col].color = get_height_color(z_value);
            col++;
        }
        row++;
        free(line);
        free_double_pointer(split_line);
    }
    close(fd);
    return (1);
}

int get_height_color(int z)
{
    if (z == 0)
        return (0x0066CC);
    else if (z <= 5)
        return (0x00CC66);
    else if (z <= 10)
        return (0xCCCC00);
    else
        return (0xCC0066);
}
