/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:28:33 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 01:28:35 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_atoi_alt(char *str, int *i)
{
	int alt = 0;
	int sign;

	sign = 1;
	if (*(str + *i) == '-')
		(*i)++;
	else
		sign = -sign;
	while (*(str + *i) >= '0' && *(str + *i) <= '9')
	{
		alt = alt * 10 + *(str + *i) - '0';
		(*i)++;
	}
	return (alt * sign);
}

void initbivector(t_camera *camera, t_vec3 *model, t_bivec3 *model_t)
{
	int i;
	t_coord sqr;
	
	sqr.l = 0;
	i = 0;
	while (sqr.l < (*camera).model_height)
	{
		sqr.c = 0;
		while (sqr.c < (*camera).model_width - 1)
		{
			(*(model_t + i)).a = *(model + sqr.l * (*camera).model_width + sqr.c);
			(*(model_t + i)).b = *(model + sqr.l * (*camera).model_width + sqr.c + 1);
			++sqr.c;
			++i;
		}
		++sqr.l;
	}
	sqr.c = 0;
	while (sqr.c < (*camera).model_width)
	{
		sqr.l = 0;
		while (sqr.l < (*camera).model_height - 1)
		{
			(*(model_t + i)).a = *(model + sqr.l * (*camera).model_width + sqr.c);
			(*(model_t + i)).b = *(model + (sqr.l + 1) * (*camera).model_width + sqr.c);
			++sqr.l;
			++i;
		}
		++sqr.c;
	}
}

void fill3dspace(t_file *file, t_camera *camera, t_screenspace *screenspace)
{
	t_coord	sqr;
	int		i;
	int		z;
	int		x;

	(*camera).model = NULL;
	(*camera).model = malloc(((*file).lines * (*file).columns * sizeof(t_vec3))
		+ ((*file).lines * ((*file).columns - 1) + ((*file).lines - 1) * (*file).columns) * sizeof(t_bivec3)
		+ COLOR_BUFFER_SIZE * sizeof(float));
	if ((*camera).model == NULL)
		return ;
	(*camera).model_t = (t_bivec3*)((*camera).model + ((*file).lines * (*file).columns));
	(*screenspace).z_buffer = (float*)((*camera).model + ((*file).lines * (*file).columns)
		+ ((*file).lines * ((*file).columns - 1) + ((*file).lines - 1) * (*file).columns));
	z = (*file).lines / 2;
	i = 0;
	sqr.l = 0;
	sqr.c = 0;
	x = -((*file).columns / 2);
	while (i < (*file).offset)
	{
		if (*((*file).str + i) == '\n')
		{
			while (sqr.c < (*file).columns)
			{
				(*((*camera).model + sqr.l * (*file).columns + sqr.c)).is_empty = 1;
				++(sqr.c);
			}
			--z;
			++(sqr.l);
			x = -((*file).columns / 2);
			++i;
			sqr.c = 0;
		}
		if (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
		{
			(*((*camera).model + sqr.l * (*file).columns + sqr.c)).y
				= ft_atoi_alt((*file).str, &i);
			(*((*camera).model + sqr.l * (*file).columns + sqr.c)).x = x;
			(*((*camera).model + sqr.l * (*file).columns + sqr.c)).z = z;
			(*((*camera).model + sqr.l * (*file).columns + sqr.c)).is_empty = 0;
			++x;
			++(sqr.c);
		}
		while (*((*file).str + i) != ' ' && *((*file).str + i) != '\n' && *((*file).str + i))
				++i;
		while (*((*file).str + i) == ' ')
				++i;
	}
}

void set_size_camera(t_camera *camera, t_file *file)
{
	(*camera).bivec_size = (*file).lines * ((*file).columns - 1)
		+ ((*file).lines - 1) * (*file).columns;
	(*camera).model_size = (*file).lines * (*file).columns;
	(*camera).model_width = (*file).columns;
	(*camera).model_height = (*file).lines;
	((*camera).translat).z = (*file).lines / 2;
}

void	getmodel_size(t_file *file, t_camera *camera)
{
	int i = 0;
	int len = 0;

	while (i < (*file).offset)
	{
		if (*((*file).str + i) == '\n')
		{
			++((*file).lines);
			++i;
			if (len > (*file).columns)
				(*file).columns = len;
			len = 0;
		}
		if (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
		{
			++((*file).model_size);
			++len;
			while (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
				++i;
		}
		while (*((*file).str + i) != ' ' && *((*file).str + i) != '\n' && *((*file).str + i))
				++i;
		while (*((*file).str + i) == ' ')
				++i;
	}
	set_size_camera(camera, file);
}

char increasevector(t_file *file)
{
	char *strtmp;

	(*file).str_size = ((*file).str_size + (*file).read_size) << 1;
	strtmp = malloc((*file).str_size * sizeof(char));
	if (strtmp == NULL)
		return (free((*file).str), 1);
	(*file).read_size <<= 1;
	for (int i = 0; i < (*file).str_size; ++i)
		*(strtmp + i) = 0;
	for (int i = 0; i < (*file).offset; ++i)
		*(strtmp + i) = *((*file).str + i);
	free((*file).str);
	(*file).str = strtmp;
	return 0;
}

void	end_parsing(t_file *file, t_camera *camera, t_screenspace *screenspace)
{
	getmodel_size(file, camera);
	fill3dspace(file, camera, screenspace);
	if ((*camera).model == NULL)
		return (write(2, "malloc failed.\n", 15), free((*file).str), (void)0);
	initbivector(camera, (*camera).model, (*camera).model_t);
	free((*file).str);
}
void parsing(char *path, t_camera *camera, t_screenspace *screenspace)
{
	t_file file = {
		.fd = -1,
		.model_size = 0,
		.read_bytes = 0,
		.read_size = 9,
		.str_size = 10,
		.offset = 0,
		.lines = 0,
		.columns = 0,
		.str = NULL
	};
	if (path == NULL)
		return (write(2, "NULL path.\n", 11), (void)0);
	file.fd = open(path, O_RDONLY);
	if (file.fd == -1)
		return (void)0;
	file.str = malloc(file.str_size * sizeof(char));
	if (file.str == NULL)
		return (write(2, "malloc failed.\n", 15), (void)0);
	file.read_bytes = read(file.fd, file.str, file.read_size);
	file.offset += file.read_bytes; 
	while (file.read_bytes > 0)
	{
		if (file.offset + file.read_size > file.str_size)
			if (increasevector(&file))
				return (write(2, "malloc failed.\n", 15), (void)0);
		file.read_bytes = read(file.fd, file.str + file.offset, file.read_size);
		file.offset += file.read_bytes * (file.read_bytes > 0); 
	}
	end_parsing(&file, camera, screenspace);
}
