/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:00:14 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 13:02:17 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

static int	parse_with_color(char *str, char *comma_pos, int *z_value, int *color)
{
	char	*height_part;
	char	*color_part;
	int		err;

	*comma_pos = '\0';
	height_part = str;
	color_part = comma_pos + 1;
	*z_value = ft_atoi_safe(height_part, &err);
	if (err)
		return (*comma_pos = ',', 0);
	*color = ft_atoi_hex(color_part, &err);
	if (err)
		return (*comma_pos = ',', 0);
	*comma_pos = ',';
	return (1);
}

static int	parse_height_only(char *str, int *z_value, int *color)
{
	int	err;

	*z_value = ft_atoi_safe(str, &err);
	if (err)
		return (0);
	*color = get_height_color(*z_value);
	return (1);
}

int parse_height_color(char *str, int *z_value, int *color)
{
	char	*comma_pos;

	comma_pos = ft_strchr(str, ',');
	if (comma_pos)
		return (parse_with_color(str, comma_pos, z_value, color));
	else
		return (parse_height_only(str, z_value, color));
}