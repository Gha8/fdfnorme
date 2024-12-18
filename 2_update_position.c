/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:28:57 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:28:59 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void updatemodel_rot(t_camera* camera, char* keystate)
{
	if (*(keystate + XK_Right))
	{
		(*camera).cosin_y.cos = (*camera).savecosin.cos;
		(*camera).cosin_y.sin = (*camera).savecosin.sin;
	}
	else if (*(keystate + XK_Left))
	{
		(*camera).cosin_y.cos = (*camera).minsavecosin.cos;
		(*camera).cosin_y.sin = (*camera).minsavecosin.sin;
	}
	else
	{
		(*camera).cosin_y.cos = 1;
		(*camera).cosin_y.sin = 0;
	}

	if (*(keystate + XK_Up))
	{
		(*camera).cosin_x.cos = (*camera).savecosin.cos;
		(*camera).cosin_x.sin = (*camera).savecosin.sin;
	}
	else if (*(keystate + XK_Down))
	{
		(*camera).cosin_x.cos = (*camera).minsavecosin.cos;
		(*camera).cosin_x.sin = (*camera).minsavecosin.sin;
	}
	else 	
	{
		(*camera).cosin_x.cos = 1;
		(*camera).cosin_x.sin = 0;
	}
}

void translate_model(t_scene *scene, t_camera *camera, t_screenspace *screenspace, char *keystate)
{
	//calculer et sauvegarder la valeur de l'angle definit par la direction de la camera.
	(*camera).angle_y.value = (((*scene).mouse_coord.x - (*screenspace).x_offset) * M_PI) / (*screenspace).x_offset;
	(*camera).angle_y.cos = cos((*camera).angle_y.value);
	(*camera).angle_y.sin = sin((*camera).angle_y.value);
	(*camera).angle_x.value = -(((*scene).mouse_coord.y - (*screenspace).y_offset) * 1.5708) / (*screenspace).y_offset;
	(*camera).angle_x.cos = cos((*camera).angle_x.value);
	(*camera).angle_x.sin = sin((*camera).angle_x.value);
	if (*(keystate + XK_KP_Add))
		(*camera).zoom += ZOOM_STEP;
	else if (*(keystate + XK_KP_Subtract))
		(*camera).zoom -= ZOOM_STEP;
	if (*(keystate + XK_w))
	{
		(*camera).translat.z -= (*camera).step * (*camera).angle_y.cos;
		(*camera).translat.x -= (*camera).step * (*camera).angle_y.sin;
	}
	else if (*(keystate + XK_s))
	{
		(*camera).translat.z += (*camera).step * (*camera).angle_y.cos;
		(*camera).translat.x += (*camera).step * (*camera).angle_y.sin;
	}
	if (*(keystate + XK_d))
	{
		(*camera).translat.x -= (*camera).step * (*camera).angle_y.cos;
		(*camera).translat.z += (*camera).step * (*camera).angle_y.sin;
	}
	else if (*(keystate + XK_a))
	{
		(*camera).translat.x += (*camera).step * (*camera).angle_y.cos;
		(*camera).translat.z -= (*camera).step * (*camera).angle_y.sin;
	}
	if (*(keystate + XK_space))
		(*camera).translat.y += (*camera).step;
	else if (*(keystate + XK_Shift_L))
		(*camera).translat.y -= (*camera).step;
}
