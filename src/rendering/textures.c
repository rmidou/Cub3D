#include "../../includes/cub3D.h"

t_txr	get_hit_texture(t_main *m, t_ray r)
{
	if (r.hit == HIT_S)
		return (m->map.s);
	if (r.hit == HIT_E)
		return (m->map.e);
	if (r.hit == HIT_W)
		return (m->map.w);
	return (m->map.n);
}

float	add_dithering(float l, int x, int y)
{
	if (l < .15f)
		return (0.f);
	if (l < 0.25f && (x % 4 != 0 || y % 4 != 0))
		return (0.f);
	if (l < 0.25f)
		return (1.f);
	if (l < 0.5f && (x % 2 != 0 || y % 2 != 0))
		return (0.f);
	if (l < 0.5f)
		return (1.f);
	if (l < 0.75f && ((x % 2 == 1 && y % 2 == 1)
			|| (x % 2 == 0 && y % 2 == 0)))
		return (0.f);
	if (l < 0.75f)
		return (1.f);
	if (l < 0.975f && ((x % 3 == 1 && y % 3 == 1)
			|| (x % 3 == 0 && y % 3 == 0)))
		return (0.f);
	return (1.f);
}

t_clr	get_pixel_color(t_main *m, float y_pos_len, t_txr t)
{
	int		x;
	int		y;
	float	l;

	l = dist(vecf(m->plr.p.x - m->ray.p.x, 0));
	l = 1.f - (1.f / (RENDER_DIST / l));
	if (l < 0.f)
		l = 0.f;
	if (m->ray.hit == HIT_S || m->ray.hit == HIT_N)
		x = (float)t.size.x * (m->ray.p.x - floorf(m->ray.p.x));
	else
		x = (float)t.size.x * (m->ray.p.y - floorf(m->ray.p.y));
	if (m->ray.hit == HIT_N || m->ray.hit == HIT_E)
		x = (float)t.size.x - x;
	y = (y_pos_len) * (float)t.size.y;
	if (m->ray.hit == HIT_E || m->ray.hit == HIT_N)
		return (scale_clr(get_pixel(t, x - 1, y), l));
	return (scale_clr(get_pixel(t, x, y), l));
}

float	get_lighting(t_main *m)
{
	float	l;

	l = dist(vecf(m->plr.p.x - m->ray.p.x, 0));
	l = 1.f - (1.f / (RENDER_DIST / l));
	if (l < 0.f)
		l = 0.f;
	return (l);
}

void	draw_row(t_main *m, t_veci p, t_txr t, float len)
{
	t_clr	color;
	float	l;
	int		x;

	l = get_lighting(m);
	color = get_pixel_color(m, ((float)p.y / len), t);
	x = p.x;
	while (x < p.x + COL_W)
	{
		color = scale_clr(color, add_dithering(l, x, (SCREEN_H / 2)
			+ (p.y - (len / 2))));
		set_pixel(color.color_i, m->scr, x, (SCREEN_H / 2)
			+ (p.y - (len / 2)));
		x++;
	}
}

void	draw_texture(t_main *m, int x_pos)
{
	int		y;
	float	len;
	t_txr	t;

	len = get_line_height(m);
	t = get_hit_texture(m, m->ray);
	y = -1;
	while (++y < (int)len)
	{
		if ((SCREEN_H / 2) + (y - (len / 2)) < 0
			|| (SCREEN_H / 2) + (y - (len / 2)) > SCREEN_H)
			continue ;
		draw_row(m, (t_veci){x_pos, y}, t, len);
	}
}
