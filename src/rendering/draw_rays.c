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
		set_pixel(color, main->img, x0, y0);
		// voir le so long de jules
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
	//len = (64 * 640) / len;
	middle = (int)roundf(SCREEN_H / 2);
	len = (SCREEN_H * 64)/ (len * cos(deg_to_rad(ca)));
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
	int line_length;
	int x1;
	int y1;
	float	para;
	//int	tt;
	int	ca;

	para = -45.f;
	while (para <= 45.f)
	{
		line_length = 1;
		x1 = main->px + cosf(deg_to_rad(main->pa + para) - PI);
		y1 = main->py + sinf(deg_to_rad(main->pa + para) - PI);
		while (main->map[(int)round(y1/64)][(int)round(x1/64)] != '1')
		{
			line_length++;
			x1 = main->px + (cosf(deg_to_rad(main->pa + para) - PI) * line_length);
			y1 = main->py + (sinf(deg_to_rad(main->pa + para) - PI) * line_length);
		}
		//draw_line(main, main->px, main->py, x1, y1, RED_PIXEL);
		ca = fix_ang(main->pa - (main->pa + para));
		draw_3D(main, (para + 45.f) * SCREEN_W / 90, sqrtf(powf(x1 - main->px, 2) + powf(y1 - main->py, 2)), ca);
		para+= 0.05f;
	}
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->img, 0, 0);
}
