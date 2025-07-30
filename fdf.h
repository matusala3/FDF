/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:18:52 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/30 19:10:33 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "MLX42/MLX42.h"
#include <fcntl.h>
#include <math.h>

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

t_point *parse_file(char *filename);

#endif