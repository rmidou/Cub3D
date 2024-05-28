#include "../../includes/cub3D.h"

int	rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_clr	color(int r, int g, int b)
{
	return ((t_clr){.r = r, .g = g, .b = b, .color_i = rgb(255, r, g, b)});
}
