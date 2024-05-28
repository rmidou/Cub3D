#include "../../includes/cub3D.h"

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
		ray->n.y = ray->p.y + ray->dx.y;
	else
		ray->n.x = ray->p.x + ray->dy.x;
}

void	nextt(t_ray *ray)
{
	if (ray->d.y > 0.f && ray->p.y == ceilf(ray->p.y))
		ray->n.y = ray->p.y + 1.f;
	else if (ray->d.y > 0.f)
		ray->n.y = ceilf(ray->p.y);
	else if (ray->p.y == floorf(ray->p.y))
		ray->n.y = ray->p.y - 1.f;
	else
		ray->n.y = floorf(ray->p.y);
	if (ray->d.x > 0.f && ray->p.x == ceilf(ray->p.x))
		ray->n.x = ray->p.x + 1.f;
	else if (ray->d.x > 0.f)
		ray->n.x = ceilf(ray->p.x);
	else if (ray->p.x == floorf(ray->p.x))
		ray->n.x = ray->p.x - 1.f;
	else
		ray->n.x = floor(ray->p.x);
}

void	space(int c_f, t_ray *ray, int x_y)
{
	if (x_y == X_ && c_f == CEIL && ray->p.y == ceilf(ray->p.y))
		ray->n.y += 1.f;
	else if (x_y == X_ && c_f == CEIL)
		ray->n.y = ceilf(ray->p.y);
	if (x_y == X_ && c_f == FLOOR && ray->p.y == floorf(ray->p.y))
		ray->n.y -= 1.f;
	else if (x_y == X_ && c_f == FLOOR)
		ray->n.y = floorf(ray->p.y);
	if (x_y == X_)
		ray->n.x = ray->p.x;
	if (x_y == Y_ && c_f == CEIL && ray->p.x == ceilf(ray->p.x))
		ray->n.x += 1.f;
	else if (x_y == Y_ && c_f == CEIL)
		ray->n.x = ceilf(ray->p.x);
	if (x_y == Y_ && c_f == FLOOR && ray->p.x == floorf(ray->p.x))
		ray->n.x -= 1.f;
	else if (x_y == Y_ && c_f == FLOOR)
		ray->n.x = floorf(ray->p.x);
	if (x_y == Y_)
		ray->n.y = ray->p.y;
}

void	init_dir2(t_ray *r)
{
	t_vecf	dir;

	dir.y = (tan(to_rad(90.f - (FOV / 2.f))) * (SCREEN_W / 2.f));
	dir.x = (r->index * COL_W) - (SCREEN_W / 2);
	r->a = fix_ang(r->a - to_deg(atan2f(dir.y, dir.x)) + 90.f);
	if (r->a > 180.f && r->a <= 270.f)
	{
		r->d.x = sinf(to_rad(r->a));
		r->d.y = cosf(to_rad(r->a));
	}
	else if (r->a >= 270.f && r->a <= 360.f)
	{
		r->d.x = -sinf(to_rad(r->a));
		r->d.y = -cosf(to_rad(r->a));
	}
	else if (r->a > 90.f && r->a <= 180.f)
	{
		r->d.x = -sinf(to_rad(r->a));
		r->d.y = -cosf(to_rad(r->a));
	}
	else
	{
		r->d.x = sinf(to_rad(r->a));
		r->d.y = cosf(to_rad(r->a));
	}
}

void	whey(t_ray *ray)
{
	if (ray->d.x == 0)
	{
		if (ray->d.y > 0)
			space(CEIL, ray, X_);
		else
			space(FLOOR, ray, X_);
		return ;
	}
	if (ray->d.y == 0)
	{
		if (ray->d.x > 0)
			space(CEIL, ray, Y_);
		else
			space(FLOOR, ray, Y_);
		return ;
	}
	nextt(ray);
	delta(ray);
}
