/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:29:14 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:29:17 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void putPixel(int x, int y, t_screenspace *screenspace)
{
	*((*screenspace).color_buffer + (y + (*screenspace).y_offset) * WIDTH + x + (*screenspace).x_offset) = DEFAULT_VECTOR_COLOR;
}

void rotateModel(t_bivec3 *bivector, t_cosin *csX, t_cosin *csY)
{
	float x;
	float y;
	float z;

	z = (*bivector).a.z * (*csX).cos - (*bivector).a.y * (*csX).sin;
	y = (*bivector).a.y * (*csX).cos + (*bivector).a.z * (*csX).sin;
	(*bivector).a.z = z;
	(*bivector).a.y = y;
	x = (*bivector).a.x * (*csY).cos - (*bivector).a.z * (*csY).sin;
	z = (*bivector).a.z * (*csY).cos + (*bivector).a.x * (*csY).sin;
	(*bivector).a.x = x;
	(*bivector).a.z = z;
	
	z = (*bivector).b.z * (*csX).cos - (*bivector).b.y * (*csX).sin;
	y = (*bivector).b.y * (*csX).cos + (*bivector).b.z * (*csX).sin;
	(*bivector).b.z = z;
	(*bivector).b.y = y;
	x = (*bivector).b.x * (*csY).cos - (*bivector).b.z * (*csY).sin;
	z = (*bivector).b.z * (*csY).cos + (*bivector).b.x * (*csY).sin;
	(*bivector).b.x = x;
	(*bivector).b.z = z;
}

void addtranslat(t_bivec3 *bivector, t_vec3 *translat)
{
	(*bivector).a.x += (*translat).x;
	(*bivector).a.y += (*translat).y;
	(*bivector).a.z += (*translat).z;	
	(*bivector).b.x += (*translat).x;
	(*bivector).b.y += (*translat).y;
	(*bivector).b.z += (*translat).z;
}

// Fonction pour tracer une ligne avec l'algorithme DDA
void drawLineDDA(t_bivec3 *biVec, t_screenspace *screenspace, float steps)
{
    // Calculer les différences entre les points
	float xInc;
	float yInc;
    float dx = (*biVec).b.x - (*biVec).a.x;
    float dy = (*biVec).b.y - (*biVec).a.y;

    // Trouver le plus grand des deux pour déterminer le nombre d'étapes
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

    // Calculer les incréments pour chaque étape
    xInc = dx / steps;
    yInc = dy / steps;

    // Tracer la ligne point par point
    for (int i = 0; i <= steps; ++i) {
		putPixel((int)round((*biVec).a.x), (int)round((*biVec).a.y), screenspace);
        (*biVec).a.x += xInc; // Incrémenter x
        (*biVec).a.y += yInc; // Incrémenter y
    }
}


void rotatecamera(t_bivec3 *bivector, t_camera *camera)
{
	float x;
	float y;
	float z;

	x = (*bivector).a.x * (*camera).angle_y.cos - (*bivector).a.z * (*camera).angle_y.sin;
	z = (*bivector).a.z * (*camera).angle_y.cos + (*bivector).a.x * (*camera).angle_y.sin;
	(*bivector).a.x = x;
	(*bivector).a.z = z;
	x = (*bivector).b.x * (*camera).angle_y.cos - (*bivector).b.z * (*camera).angle_y.sin;
	z = (*bivector).b.z * (*camera).angle_y.cos + (*bivector).b.x * (*camera).angle_y.sin;
	(*bivector).b.x = x;
	(*bivector).b.z = z;

	z = (*bivector).a.z * (*camera).angle_x.cos - (*bivector).a.y * (*camera).angle_x.sin;
	y = (*bivector).a.y * (*camera).angle_x.cos + (*bivector).a.z * (*camera).angle_x.sin;
	(*bivector).a.z = z;
	(*bivector).a.y = y;
	z = (*bivector).b.z * (*camera).angle_x.cos - (*bivector).b.y * (*camera).angle_x.sin;
	y = (*bivector).b.y * (*camera).angle_x.cos + (*bivector).b.z * (*camera).angle_x.sin;
	(*bivector).b.z = z;
	(*bivector).b.y = y;
}

void rotateIso(t_bivec3 *bivector)
{
	float x;
	float y;
	float z;

	x = (*bivector).a.x * cos(-0.7854) - (*bivector).a.z * sin(-0.7854);
	z = (*bivector).a.z * cos(-0.7854) + (*bivector).a.x * sin(-0.7854);
	(*bivector).a.x = x;
	(*bivector).a.z = z;
	z = (*bivector).a.z * cos(-0.61548) - (*bivector).a.y * sin(-0.61548);
	y = (*bivector).a.y * cos(-0.61548) + (*bivector).a.z * sin(-0.61548);
	(*bivector).a.z = z;
	(*bivector).a.y = y;
	
	x = (*bivector).b.x * cos(-0.7854) - (*bivector).b.z * sin(-0.7854);
	z = (*bivector).b.z * cos(-0.7854) + (*bivector).b.x * sin(-0.7854);
	(*bivector).b.x = x;
	(*bivector).b.z = z;
	z = (*bivector).b.z * cos(-0.61548) - (*bivector).b.y * sin(-0.61548);
	y = (*bivector).b.y * cos(-0.61548) + (*bivector).b.z * sin(-0.61548);
	(*bivector).b.z = z;
	(*bivector).b.y = y;
}

void project_iso(t_camera *camera, t_screenspace *screenspace, int i)
{
	float		zoom;
	t_bivec3	bivector;

	i = 0;
	while (i < (*camera).bivec_size)
	{
		if (!((*((*camera).model_t + i)).a.is_empty) && !((*((*camera).model_t + i)).b.is_empty)) 
		{
			rotateModel((*camera).model_t + i, &((*camera).cosin_x), &((*camera).cosin_y));
			bivector = *((*camera).model_t + i);
			rotateIso(&bivector);
			addtranslat(&bivector, &((*camera).translat));
			rotatecamera(&bivector, camera);
			zoom = (*camera).zoom / 15;
			bivector.a.x = (bivector).a.x * zoom;
			bivector.a.y = (bivector).a.y * zoom;
			bivector.b.x = (bivector).b.x * zoom;
			bivector.b.y = (bivector).b.y * zoom;
			if ((bivector.a.x >= -((*screenspace).x_offset) && bivector.a.x <= ((*screenspace).x_offset))
					&& (bivector.a.y >= -((*screenspace).y_offset) && bivector.a.y <= ((*screenspace).y_offset))
					&& (bivector.b.x >= -((*screenspace).x_offset) && bivector.b.x <= ((*screenspace).x_offset))
					&& (bivector.b.y >= -((*screenspace).y_offset) && bivector.b.y <= ((*screenspace).y_offset)))
				drawLineDDA(&bivector, screenspace, 0);
		}
		++i;
	}
}

void project(t_camera *camera, t_screenspace *screenspace, int i)
{
	float		z;
	t_bivec3	bivector;
	i = 0;
	while (i < (*camera).bivec_size)
	{
		if (!((*((*camera).model_t + i)).a.is_empty) && !((*((*camera).model_t + i)).b.is_empty)) 
		{
			rotateModel((*camera).model_t + i, &((*camera).cosin_x), &((*camera).cosin_y));
			bivector = *((*camera).model_t + i);
			addtranslat(&bivector, &((*camera).translat));
			rotatecamera(&bivector, camera);
			if (((bivector).a.z) > ZMIN && ((bivector).b.z) > ZMIN)
			{
				z = (*camera).zoom / (bivector).a.z;
				bivector.a.x = (bivector).a.x * z;
				bivector.a.y = (bivector).a.y * z;
				z = (*camera).zoom / (bivector).b.z;
				bivector.b.x = (bivector).b.x * z;
				bivector.b.y = (bivector).b.y * z;
				if ((bivector.a.x >= -((*screenspace).x_offset) && bivector.a.x <= ((*screenspace).x_offset))
						&& (bivector.a.y >= -((*screenspace).y_offset) && bivector.a.y <= ((*screenspace).y_offset))
						&& (bivector.b.x >= -((*screenspace).x_offset) && bivector.b.x <= ((*screenspace).x_offset))
						&& (bivector.b.y >= -((*screenspace).y_offset) && bivector.b.y <= ((*screenspace).y_offset)))
					drawLineDDA(&bivector, screenspace, 0);
			}
		}
		++i;
	}
}

void clear(t_scene *scene)
{
	//Clear Background.
	for (int i = 0; i < COLOR_BUFFER_SIZE; ++i)
		*((*(*scene).screenspace).color_buffer + i) = BACKGROUND_COLOR;
}

void draw_square(t_scene *scene , int size, t_vec2 cursor)
{
	t_screenspace *screenspace = (*scene).screenspace;
	int x;

	size = (size >> 1) + ((size <= 1) >> 1);

	for (int y = (*screenspace).y_offset - size + cursor.y; y < (*screenspace).y_offset + size + cursor.y; ++y)
	{
		if ((y < HEIGHT) && (y > -1))
		{
			x = (*screenspace).x_offset - size + cursor.x;
			for (; x < (*screenspace).x_offset + size + cursor.x; ++x)
				if ((x < WIDTH) && (x > -1))
					*((*(*scene).screenspace).color_buffer + y * WIDTH + x) = 0x0000ff00;
		}
	}
}
