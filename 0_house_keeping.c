#include "fdf.h"
int create_window(t_data *img)
{
	//API Intialisation.
	(*img).mlx = mlx_init();
	if ((*img).mlx == NULL)
		return 0;

	//Create window.
	(*img).mlx_win = mlx_new_window((*img).mlx, WIDTH, HEIGHT, "MLX_TEST!");
	if ((*img).mlx_win == NULL)
		return 0;

	//Image initialisation.
	(*img).img = mlx_new_image((*img).mlx, WIDTH, HEIGHT);
	if ((*img).img == NULL)
		return 0;
	(*img).addr = (int *)mlx_get_data_addr(
		(*img).img,
		&((*img).bits_per_pixel),
		&((*img).line_length),
		&((*img).endian));
	return 1;
}
