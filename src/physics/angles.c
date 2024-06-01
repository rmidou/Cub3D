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
	float	ang;

	ang = a;
	if (ang > 360.f)
		ang -= 360.f;
	if (ang < 0.f)
		ang += 360.f;
	if (ang > 360.f || ang < 0.f)
		return (fix_ang(ang));
	return (ang);
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
