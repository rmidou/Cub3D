#include "../../includes/cub3D.h"

float	dist(t_vecf v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

void	delta(t_ray *ray)
{
	float	vecx;
	float	vecy;

	ray->dx.x = ray->n.x - ray->p.x;
	ray->dy.y = ray->n.y - ray->p.y;
	ray->dx.y = (ray->d.x / ray->d.y) * ray->dx.x;
	ray->dy.x = (ray->d.y / ray->d.x) * ray->dy.y;
	vecx = dist(ray->dx);
	vecy = dist(ray->dy);
	if (vecx < vecy)
		ray->n.y = ray->dx.y;
	else
		ray->n.x = ray->dy.x;
}

void	next(t_ray *ray)
{
	if (ray->d.y > 0)
		ray->n.y = ceilf(ray->d.y);
	else
		ray->n.y =floorf(ray->d.y);
	if (ray->d.x > 0)
		ray->n.x = ceilf(ray->d.x);
	else
		ray->n.x =floorf(ray->d.x);
}

void	space(int c_f, t_ray *ray, int x_y)
{
	if (!x_y)
	{
		if (!c_f)
			ray->n.y = ceilf(ray->d.y);
		else
			ray->n.y = floorf(ray->d.y);
		ray->n.x = ray->p.x;
	}
	else
	{
		if (!c_f)
			ray->n.x = ceilf(ray->d.x);
		else
			ray->n.x = floorf(ray->d.x);
		ray->n.y = ray->p.y;
	}
}

void	whey(t_ray *ray)
{
	ray->d.x = cosf(ray->a);
	ray->d.y = sinf(ray->a);
	if (ray->d.x == 0)
	{
		if (ray->d.y > 0)
			space(0, ray, 0);
		else
			space(1, ray, 0);
		return;
	}
	if (ray->d.y == 0)
	{
		if (ray->d.x > 0)
			space(0, ray, 1);
		else
			space(1, ray, 1);
		return;
	}
	next(ray);
	delta(ray);
}
