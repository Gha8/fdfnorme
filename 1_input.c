/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:28:43 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:28:45 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int close_window(void *mlx)
{
	mlx_loop_end(mlx);
    return (0);
}

int keyPress(int keycode, void *keystate)
{
	(void)keystate;
	*((char *)keystate + keycode) = 1;
	if (keycode == XK_i)
		*((char *)keystate + KEYSIZE - 1) = 1;
	if (keycode == XK_p)
		*((char *)keystate + KEYSIZE - 1) = 0;
		
	return 0;
}

int keyRelease(int keycode, void *keystate)
{
	(void)keystate;
	*((char *)keystate + keycode) = 0;
	return 0;
}

int updateMouseCoordinates(int x, int y, void *scene)
{
	(*(t_scene *)scene).mouse_coord.x = x;
	(*(t_scene *)scene).mouse_coord.y = y;
	return 0;
}

void ft_input(t_scene *scene)
{
	mlx_hook((*scene).mlx_win, 17, 0, close_window, (*scene).mlx);
	mlx_hook((*scene).mlx_win, 2, 1L<<0, keyPress, (*scene).keystate);
	mlx_hook((*scene).mlx_win, 3, 1L<<1, keyRelease, (*scene).keystate);
	mlx_hook((*scene).mlx_win, 6, 1L<<6, updateMouseCoordinates, scene);
}
