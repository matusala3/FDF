/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:15:56 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 18:57:54 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_map	*init_map_structure(int rows, int cols)
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

int	allocate_map_rows(t_map *map_data, int rows, int cols)
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

int	process_line_data(char **split_line, t_map *map_data, int row)
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

int	process_single_line(char *line, t_map *map_data, int row)
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

int	fill_map_data(char *filename, t_map *map_data)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	row = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!process_single_line(line, map_data, row))
		{
			free(line);
			close(fd);
			return (0);
		}
		row++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
