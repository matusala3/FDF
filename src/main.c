/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:19:53 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/30 19:10:23 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int main(int argc, char **argv)
{
	t_map *map;

	if(argc != 2)
	{
		ft_printf("Usage: ./fdf <filename.fdf>\n");
		return (0);
	}
    map = parse_file(argv[1]);
	if(!map)
	{
		ft_printf("Error: Failed to parse file\n");
		return(1);
	}
	return(0);
}
