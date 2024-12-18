/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoolszew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:32:19 by zoolszew          #+#    #+#             */
/*   Updated: 2024/12/18 00:33:35 by zoolszew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include <X11/keysym.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# define STR_SIZE 1000
# define CURSOR_SPEED 0.4
# define CURSOR_SIZE 10
# define ZMIN 2
# define ZMAX 1000
# define REF_MODEF_DEPTH 100
# define X 0
# define Y 0
# define FOCAL_DISTANCE 5
# define STEP 0.4
# define ROTATION_MODEL_STEP 0.01
# define ROTATION_CAMERA_STEP 0.01
# define HEIGHT 900
# define WIDTH 1600
# define SHEIGHT HEIGHT / 2
# define SWIDTH WIDTH / 2
# define ZOOM 800
# define ZOOM_STEP 10
# define DEFAULT_VECTOR_COLOR 0x00000000
# define BACKGROUND_COLOR 0x00ffffff //TRGB
# define COLOR_BUFFER_SIZE WIDTH * HEIGHT
# define KEYSIZE 65537

typedef struct s_file
{
	int		fd;
	int		model_size;
	int		read_bytes;
	int		read_size;
	int		str_size;
	int		offset;
	int		lines;
	int		columns;
	char	*str;
}	t_file;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_coordinate2
{	
	int	c;
	int	l;
}	t_coord;

typedef struct s_vec2int
{	
	int	x;
	int	y;
}	t_vec2int;
typedef struct s_vec2
{	
	float	x;
	float	y;
}	t_vec2;
typedef struct s_cosin
{	
	float	cos;
	float	sin;
}	t_cosin;
typedef struct s_angle
{
	float	value;
	float	cos;
	float	sin;
}	t_angle;
typedef struct s_vec3
{
	char	is_empty;
	int		color;
	float	x;
	float	y;
	float	z;
}	t_vec3;
typedef struct s_bivec3
{
	t_vec3	a;
	t_vec3	b;
}	t_bivec3;
typedef struct s_camera
{
	int			bivec_size;
	int			model_size;
	int			model_width;
	int			model_height;
	float		step;
	float		zoom;
	t_angle		angle_x;
	t_angle		angle_y;
	t_angle		angle_z;
	t_cosin		cosin_x;
	t_cosin		cosin_y;
	t_cosin		cosin_z;
	t_cosin		savecosin;
	t_cosin		minsavecosin;	
	t_vec3		translat;
	t_vec3		model_rot;
	float		focal_dist;
	t_vec3		*model;
	t_bivec3	*model_t;
}	t_camera;

/*Screen space*/
typedef struct s_screenspace
{
	int		x_offset;
	int		y_offset;
	int		*color_buffer;
	float	*z_buffer;
	t_vec2	cursor;
}	t_screenspace;

/*Scene*/
typedef struct s_scene
{
	char			keystate[KEYSIZE];
	char			str[STR_SIZE];
	t_vec2int		mouse_coord;
	t_camera		*camera;
	t_screenspace	*screenspace;
	void			*mlx;
	void			*mlx_win;
	void			*img;
}	t_scene;

void	parsing(char *path, t_camera *camera, t_screenspace *screenspace);
int		create_window(t_data *img);
void	initcamera(t_camera *camera);
void	initscreenspace(t_screenspace *screenspace, t_data *img);
void	init_scene(t_scene *scene, t_data *img, t_camera *camera,
			t_screenspace *screenspace);
void	ft_input(t_scene *scene);
void	translate_model(t_scene *scene, t_camera *camera,
			t_screenspace *screenspace, char *keystate);
void	updatemodel_rot(t_camera * camera, char *keystate);
void	clear(t_scene *scene);
void	draw_square(t_scene *scene, int size, t_vec2 cursor);
void	project(t_camera *camera, t_screenspace *screenspace, int i);
void	project_iso(t_camera *camera, t_screenspace *screenspace, int i);
int		ft_atoi_alt(char *str, int *i);
void	initbivector(t_camera *camera, t_vec3 *model, t_bivec3 *model_t);
void	fill3dspace(t_file *file, t_camera *camera, t_screenspace *screenspace);
void	getmodel_size(t_file *file, t_camera *camera);
char	increasevector(t_file *file);
#endif 
