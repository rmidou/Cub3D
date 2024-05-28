#include "../../includes/cub3D.h"

int	rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_clr	color(int r, int g, int b)
{
	return ((t_clr){.r = r, .g = g, .b = b, .color_i = rgb(255, r, g, b)});
}

t_clr	scale_clr(t_clr c, float f)
{
	return (color((float)c.r * f, (float)c.g * f, (float)c.b * f));
}

t_clr	get_hit_color(t_main *m, t_ray r)
{
	float	l;
	t_clr	clrn;
	t_clr	clrs;
	t_clr	clre;
	t_clr	clrw;

	l = dist(vecf(m->plr.p.x - r.p.x, 0));
	l = 1.f - (1.f / (RENDER_DIST / l));
	if (l < 0.f)
		l = 0.f;
	clrn = scale_clr(color(255, 0, 0), l);
	clrs = scale_clr(color(0, 0, 255), l);
	clre = scale_clr(color(0, 255, 0), l);
	clrw = scale_clr(color(255, 0, 255), l);
	if (r.hit == HIT_S)
		return (clrs);
	if (r.hit == HIT_E)
		return (clre);
	if (r.hit == HIT_W)
		return (clrw);
	return (clrn);
}
