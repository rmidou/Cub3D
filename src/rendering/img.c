#include "../../includes/cub3D.h"

void	set_pixel(int color, void *img, int x, int y)
{
	t_txr	data;
	int		pixel;

	data.data = mlx_get_data_addr(img, &data.bpp, &data.line, &data.endian);	
	pixel = (y * data.line) + (x * (data.bpp / 8));
	if (data.endian == 1)
	{
		data.data[pixel + 0] = (color >> 24);
		data.data[pixel + 1] = (color >> 16) & 0xFF;
		data.data[pixel + 2] = (color >> 8) & 0xFF;
		data.data[pixel + 3] = (color) & 0xFF;
	}
	else if (data.endian == 0)
	{
		data.data[pixel + 0] = (color) & 0xFF;
		data.data[pixel + 1] = (color >> 8) & 0xFF;
		data.data[pixel + 2] = (color >> 16) & 0xFF;
		data.data[pixel + 3] = (color >> 24);
	}
}
