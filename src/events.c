/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/05 00:00:00 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int handle_keypress(int keycode, t_graphics *gfx)
{
    ft_printf("Key pressed: %d\n", keycode);
    
    if (keycode == 65307)
    {
        ft_printf("ESC pressed - exiting\n");
        cleanup_graphics(gfx);
        exit(0);
    }
    
    return (0);
}

int handle_close(t_graphics *gfx)
{
    ft_printf("Window close button pressed\n");
    cleanup_graphics(gfx);
    exit(0);
    return (0);
}