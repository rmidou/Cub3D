#include "../../includes/cub3D.h"

t_vecf	ang_to_vecf(float a)
{
	return (vecf(cosf(a), sinf(a)));
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
