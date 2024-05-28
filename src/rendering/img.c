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

void	draw_line(t_main *main, t_veci start, t_veci end, int color)
{
	int		i;
	int		steps;
	t_veci	d;
	t_vecf	inc;
	t_veci	pos;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = abs(d.y);
	if (abs(d.x) > abs(d.y))
		steps = abs(d.x);
	inc.x = d.x / (float)steps;
	inc.y = d.y / (float)steps;
	pos.x = start.x;
	pos.y = start.y;
	i = 0;
	while (i <= steps)
	{
		set_pixel(color, main->scr, round(pos.x), round(pos.y));
		pos.x += inc.x;
		pos.y += inc.y;
		i++;
	}
}
