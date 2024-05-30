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

t_clr	get_pixel_color(t_main *m, float y_pos_len, t_txr t, t_ray r)
{
	int		x;
	int		y;
	float	l;

	l = dist(vecf(m->plr.p.x - r.p.x, 0));
	l = 1.f - (1.f / (RENDER_DIST / l));
	if (l < 0.f)
		l = 0.f;
	if (r.hit == HIT_S || r.hit == HIT_N)
		x = (float)t.size.x * (r.p.x - floorf(r.p.x));
	else
		x = (float)t.size.x * (r.p.y - floorf(r.p.y));
	if (r.hit == HIT_N || r.hit == HIT_E)
		x = (float)t.size.x - x;
	y = (y_pos_len) * (float)t.size.y;
	if (r.hit == HIT_E || r.hit == HIT_N)
		return (scale_clr(get_pixel(t, x - 1, y), l));
	return (scale_clr(get_pixel(t, x, y), l));
}

void	draw_texture(t_main *m, int x_pos, t_ray r)
{
	int		x;
	int		y;
	float	len;
	t_clr	color;
	t_txr	t;

	len = get_line_height(m, r);
	t = get_hit_texture(m, r);
	y = 0;
	while (y < (int)len)
	{
		color = get_pixel_color(m, ((float)y / len), t, r);
		x = x_pos;
		while (x < x_pos + COL_W)
		{
			set_pixel(color.color_i, m->scr, x, (SCREEN_H / 2)
				+ (y - (len / 2)));
			x++;
		}
		y++;
	}
}
