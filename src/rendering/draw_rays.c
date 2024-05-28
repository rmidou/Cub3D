#include "../../includes/cub3D.h"

void	draw_line(t_main *main, t_veci start, t_veci end, int color)
{
	int		i;
	t_veci	d;
    int 	steps;
	t_vecf	inc;
	t_veci	pos;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = abs(d.x) > abs(d.y) ? abs(d.x) : abs(d.y); 
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

// int    draw_line(t_main *main, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx;
// 	int dy;
// 	int sx;
// 	int sy;
// 	int err;
// 	int e2;
// 	int	tt;

// 	tt = 0;
// 	dx = abs(x1 - x0);
// 	dy = -abs(y1 - y0);
// 	sx = (x0 < x1) ? 1 : -1;
// 	sy = (y0 < y1) ? 1 : -1;
// 	err = dx + dy;
// 	while (1)
// 	{
// 		set_pixel(color, main->img, x0, y0);
// 		// voir le so long de jules
// 		tt += 1;
// 	    if (x0 == x1 && y0 == y1)
// 			break;
// 	    e2 = 2 * err;
// 	    if (e2 >= dy)
// 		{
// 	        err += dy;
// 	        x0 += sx;
// 	    }
// 	    if (e2 <= dx)
// 		{
// 	        err += dx;
// 	        y0 += sy;
// 	    }
// 	}
// 	return (tt);
// }

void	draw_3D(t_main *main, int x, float len)
{
	int		i;
	int		red;
	int		grn;
	int		blu;
	float	h;

	i = x;
	h = SCREEN_DIST / (2.f * len);
	len = (SCREEN_H / 2) * (h / SH) * 2.f;
	if (len > SCREEN_H)
		len = SCREEN_H;
	red = (unsigned char)(150.f * (1.f - (RENDER_DIST / len)));
	grn = (unsigned char)(100.f * (1.f - (RENDER_DIST / len)));
	blu = (unsigned char)(255.f * (1.f - (RENDER_DIST / len)));

	while (i < x + COL_W)
	{
		draw_line(main, (t_veci){i, (SCREEN_H / 2) - len / 2}, (t_veci){i, (SCREEN_H / 2) + len / 2}, rgb(255, red, grn, blu));
		i++;
	}
}

char	get_block(t_main *main, t_ray r)
{
	t_veci	i;

	i.x = (int)floorf(r.p.x);
	i.y = (int)floorf(r.p.y);
	if (r.p.x == floorf(r.p.x) && r.d.x < .0f)
		i.x--;
	if (r.p.y == floorf(r.p.y) && r.d.y < .0f)
		i.y--;
	if (i.y < 0.f || i.y >= main->map.size.y
	||	i.x < 0.f || i.x >= main->map.size.x)
		return ('1');
	return (main->map.map[i.y][i.x]);
}

int	out_of_bounds(t_main *main, t_vecf p)
{
	if (p.x < 0.f || p.x > main->map.size.x
	|| p.y < 0.f || p.y > main->map.size.y)
		return (0);
	return (1);
}

int	get_height(t_main *m, t_vecf p)
{
	(void)m;
	(void)p;
	return (0);
}

void    draw_view_line(t_main *main)
{
	// float x1;
	// float y1;
	//float	para;
	int		col_index;
	//int	tt;
	//int	ca;
	t_ray r;

	// CHANGER MODE DE CALCUL DES RAYONS
	//para = -45.f;
	col_index = -1;
	while (++col_index < (SCREEN_W / COL_W))
	{
		r.a = fix_ang(main->plr.a);
		r.index = col_index;
		init_dir2(&r);
		r.p.x = main->plr.p.x;
		r.p.y = main->plr.p.y;
		while (out_of_bounds(main, r.p) && get_block(main, r) != '1')
		{
			whey(&r);
			r.p = r.n;
		}
		//draw_line(main, main->px, main->py, x1, y1, RED_PIXEL);
		//ca = fix_ang(main->pa - (main->pa + para));
		if (out_of_bounds(main, r.p))
			draw_3D(main, col_index * COL_W, sqrtf(powf(r.p.x - main->plr.p.x, 2) + powf(r.p.y - main->plr.p.y, 2)));
	}
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->scr.img, 0, 0);
}
