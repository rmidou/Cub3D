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

void	draw_3D(t_main *main, int x, float len)
{
	int		i;
	t_veci	start;
	t_veci	end;
	float	screen;

	screen = tanf(90.f - (FOV / 2.f)) * (SCREEN_SIZE / 2.f);

	i = x;
	len = ((len / screen) * SCREEN_SIZE / 2.f) * ((float)SCREEN_W / SCREEN_SIZE) * 2;
	if (len > SCREEN_H)
		len = SCREEN_H;
	while (i < x + 1)
	{
		start = (t_veci){i, (int)roundf(SCREEN_H / 2) - len / 2};
		end = (t_veci){i, (int)roundf(SCREEN_H / 2) + len / 2};
		draw_line(main, start, end, RED_PIXEL);
		i++;
	}
}

void	init_ray(t_ray *r, t_main *main, float ang)
{
	r->p = main->plr.p;
	r->a = main->plr.a + ang;
}

char	get_map_block(t_vecf p, t_main *main)
{
	int	x;
	int	y;

	x = (int)floorf(p.x);
	y = (int)floorf(p.y);
	if (x < 0 || x >= main->map.size.x
	|| y < 0 || y >= main->map.size.y)
		return ('1');
	return (main->map.map[y][x]);
}

void    draw_view_line(t_main *main)
{
	float	ang;
	t_ray	r;

	ang = -(FOV / 2.f);
	while (ang <= (FOV / 2.f))
	{
		init_ray(&r, main, ang);
		while (get_map_block(r.p, main) == '0')
		{
			whey(&r);
			r.p = r.n;
		}
		draw_3D(main, ((ang + (FOV / 2.f)) / 0.05f) * (SCREEN_W / (FOV / 0.05f)), dist((t_vecf){r.p.x - main->plr.p.x, r.p.y - main->plr.p.y}));
		ang += 0.05f;
	}
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->scr.img, 0, 0);
}
