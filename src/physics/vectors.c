#include "../../includes/cub3D.h"

t_vecf	vecf(float x, float y)
{
	return ((t_vecf){.x = x, .y = y});
}

float	dist(t_vecf v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vecf	norm(t_vecf v)
{
	float	len;

	len = dist(v);
	return (vecf(v.x / len, v.y / len));
}

t_vecf	add(t_vecf u, t_vecf v)
{
	return (vecf(u.x + v.x, u.y + v.y));
}

t_vecf	sub(t_vecf u, t_vecf v)
{
	return (vecf(u.x - v.x, u.y - v.y));
}
