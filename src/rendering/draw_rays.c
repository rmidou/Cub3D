#include "../../includes/cub3D.h"

int    draw_line(t_main *main, int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	int	tt;

	tt = 0;
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		set_pixel(color, main->scr.img, x0, y0);
		tt += 1;
	    if (x0 == x1 && y0 == y1)
			break;
	    e2 = 2 * err;
	    if (e2 >= dy)
		{
	        err += dy;
	        x0 += sx;
	    }
	    if (e2 <= dx)
		{
	        err += dx;
	        y0 += sy;
	    }
	}
	return (tt);
}

void	draw_3D(t_main *main, int x, float len, int ca)
{
	int		i;
	int		middle;

	i = x;
	middle = (int)roundf(SCREEN_H / 2);
	len = SCREEN_H / (len * cos(deg_to_rad(ca)));
	if (len > SCREEN_H)
		len = SCREEN_H;
	while (i < x + 1)
	{
		draw_line(main, i, middle - len / 2, i, middle + len / 2, RED_PIXEL);
		i++;
	}
}

void    draw_view_line(t_main *main)
{
	float 	x1;
	float 	y1;
	float	para;
	int	ca;

	para = -45.f;
	while (para <= 45.f)
	{
		x1 = main->px + cosf(deg_to_rad(main->pa + para) - PI);
		y1 = main->py + sinf(deg_to_rad(main->pa + para) - PI);
		while (main->map.map[(int)roundf(y1)][(int)round(x1)] == '0')
		{
			ft_printf("%d %d\n", (int)roundf(y1), (int)roundf(x1));
			if (y1 < 0.f || y1 > (float)main->map.size.y
			||	x1 < 0.f || x1 > (float)main->map.size.x)
				break ;
			x1 += cosf(deg_to_rad(main->pa + para) - PI);
			y1 += sinf(deg_to_rad(main->pa + para) - PI);
		}
		ca = fix_ang(main->pa - (main->pa + para));
		draw_3D(main, (para + 45.f) * SCREEN_W / 90, sqrtf(powf(x1 - main->px, 2) + powf(y1 - main->py, 2)), ca);
		para+= 0.05f;
	}
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->scr.img, 0, 0);
}
