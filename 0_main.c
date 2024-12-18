/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:28:22 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:28:24 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int gameLoop(t_scene *scene)
{
	clear(scene);
	translate_model(scene, (*scene).camera, (*scene).screenspace, (*scene).keystate);
	updatemodel_rot((*scene).camera, (*scene).keystate);
	if (*((*scene).keystate + KEYSIZE - 1))
		project_iso((*scene).camera, (*scene).screenspace, 0);
	else
		project((*scene).camera, (*scene).screenspace, 0);
	//Display image.
	mlx_put_image_to_window(
		(*scene).mlx,
		(*scene).mlx_win,
		(*scene).img,
		0,
		0);
	//print mouse coordinates.	
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 40, 0, "UP          : space.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 60, 0, "DOWN        : shiftL.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 80, 0, "FORWARD     : w.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 100, 0,"BACKWARD    : s.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 120, 0,"LEFT        : a.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 140, 0,"RIGHT       : d.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 160, 0,"Perspective : p.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 180, 0,"Isometrique : i.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 200, 0,"Rotation    : arrrows.");
	if (*((*scene).keystate + XK_Escape))
		mlx_loop_end((*scene).mlx);
	return 0;
}

int main(int argc, char **argv)
{
	t_data	img;
	t_camera camera;
	t_screenspace screenspace;
	t_scene scene;

	if (argc != 2)
		return (write(2, "Wrong number of argument.\n", 26));
	//map parsing
	parsing(*(argv + 1), &camera, &screenspace);
	if (camera.model == NULL)
		return 1;
	//Creation window/color_buffer.
	if (!create_window(&img))
		return 1;
	//scene initialisation.
	initcamera(&camera);
	initscreenspace(&screenspace, &img);
	init_scene(&scene, &img, &camera, &screenspace);

	//Hooks aka Input Handlers.
	ft_input(&scene);

	//Move the mouse to the center.
	mlx_mouse_move(img.mlx, img.mlx_win, WIDTH / 2, HEIGHT / 2);

	//Start GameLoop.	
	mlx_loop_hook(img.mlx, gameLoop, &scene);
	mlx_loop(img.mlx);
	return (free(camera.model), 0);
}
