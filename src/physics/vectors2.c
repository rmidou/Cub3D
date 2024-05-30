#include "../../includes/cub3D.h"

t_vecf	scale(t_vecf v, float f)
{
	return (vecf(v.x * f, v.y * f));
}

int	get_line_height(t_main *m, t_ray r)
{
	t_vecf	ray_path;
	float	len;

	ray_path = sub(r.p, m->plr.p);
	ray_path = rotate(ray_path, -(m->plr.a));
	len = abs((int)((tanf(to_rad(90.f - (FOV / 2.f))) * SCREEN_W)
				/ (2.f * ray_path.x)));
	return (len);
}
