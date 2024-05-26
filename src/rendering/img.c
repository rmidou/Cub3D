#include "../../includes/cub3D.h"

void	set_pixel(int color, t_txr t, int x, int y)
{
	int		pixel;

	pixel = (y * t.line) + (x * (t.bpp / 8));
	if (t.endian == 1)
	{
		t.data[pixel + 0] = (color >> 24);
		t.data[pixel + 1] = (color >> 16) & 0xFF;
		t.data[pixel + 2] = (color >> 8) & 0xFF;
		t.data[pixel + 3] = (color) & 0xFF;
	}
	else if (t.endian == 0)
	{
		t.data[pixel + 0] = (color) & 0xFF;
		t.data[pixel + 1] = (color >> 8) & 0xFF;
		t.data[pixel + 2] = (color >> 16) & 0xFF;
		t.data[pixel + 3] = (color >> 24);
	}
}
