#include "../../includes/cub3D.h"

t_vecf	ang_to_vecf(float a)
{
	float	rad;

	rad = to_rad(a);
	return (vecf(cosf(rad), sinf(rad)));
}

float	to_deg(float a)
{
	return ((a * 180.f) / PI);
}

float	to_rad(float a)
{
	return ((a * PI) / 180.f);
}

float	fix_ang(float a)
{
	if (a < 0.f)
		a += 360.f;
	if (a > 360.f)
		a -= 360.f;
	return (a);
}

t_vecf	rotate(t_vecf v, float a)
{
	float	rad;
	float	s;
	float	c;

	rad = to_rad(a);
	s = sinf(rad);
	c = cosf(rad);
	return (vecf((c * v.x) - (s * v.y), (s * v.x) + (c * v.y)));
}
