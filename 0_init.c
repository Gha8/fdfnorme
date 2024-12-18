/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:28:08 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:28:11 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initcamera(t_camera *camera)
{
	(*camera).step = ((float)((*camera).model_height)
			*(float)STEP) / (float)REF_MODEF_DEPTH;
	(*camera).zoom = ZOOM;
	(*camera).focal_dist = FOCAL_DISTANCE;
	((*camera).model_rot).x = 0;
	((*camera).model_rot).y = 0;
	((*camera).model_rot).z = 0;
	((*camera).translat).x = X;
	((*camera).translat).y = Y;
	(*camera).angle_x.cos = 1;
	(*camera).angle_x.sin = 1;
	(*camera).angle_y.cos = 1;
	(*camera).angle_y.sin = 1;
	(*camera).savecosin.cos = cos(ROTATION_MODEL_STEP);
	(*camera).savecosin.sin = sin(ROTATION_MODEL_STEP);
	(*camera).minsavecosin.cos = cos(-ROTATION_MODEL_STEP);
	(*camera).minsavecosin.sin = sin(-ROTATION_MODEL_STEP);
}

void	initscreenspace(t_screenspace *screenspace, t_data *img)
{
	(*screenspace).color_buffer = (*img).addr;
	(*screenspace).x_offset = SWIDTH;
	(*screenspace).y_offset = SHEIGHT;
	((*screenspace).cursor).x = 0;
	((*screenspace).cursor).y = 0;
}

void	init_scene(t_scene *scene, t_data *img,
	t_camera *camera, t_screenspace *screenspace)
{
	int	i;

	((*scene).mouse_coord).x = 0;
	((*scene).mouse_coord).y = 0;
	(*scene).camera = camera;
	(*scene).screenspace = screenspace;
	(*scene).mlx = (*img).mlx;
	(*scene).mlx_win = (*img).mlx_win;
	(*scene).img = (*img).img;
	i = 0;
	while (i < KEYSIZE)
		*(((*scene).keystate) + i++) = 0;
	i = 0;
	while (i < STR_SIZE)
		*(((*scene).str) + i++) = 0;
}
