/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:36:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 18:49:58 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_map	*parse_file(char *filename)
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

int	get_file_dimensions(char *filename, int *rows, int *cols)
{
	int		fd;
	char	*line;
	int		current_cols;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	*rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
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
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	count_columns(char *line)
{
	char	**split;
	int		count;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	count = 0;
	i = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
			count++;
		i++;
	}
	free_double_pointer(split);
	return (count);
}

t_map	*allocate_map(int rows, int cols)
{
	t_map	*map_data;

	map_data = init_map_structure(rows, cols);
	if (!map_data)
		return (NULL);
	if (!allocate_map_rows(map_data, rows, cols))
		return (NULL);
	return (map_data);
}
