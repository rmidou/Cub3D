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
		ray->n.y = ray->p.y + ray->dx.y;
	else
		ray->n.x = ray->p.x + ray->dy.x;
}

void	nextt(t_ray *ray)
{
	if (ray->d.y > 0.f)
	{
		if (ray->p.y == ceilf(ray->p.y))
			ray->n.y = ray->p.y + 1.f;
		else
			ray->n.y = ceilf(ray->p.y);
	}
	else
	{
		if (ray->p.y == floorf(ray->p.y))
			ray->n.y = ray->p.y - 1.f;
		else
			ray->n.y = floorf(ray->p.y);
	}
	if (ray->d.x > 0.f)
	{
		if (ray->p.x == ceilf(ray->p.x))
			ray->n.x = ray->p.x + 1.f;
		else
			ray->n.x = ceilf(ray->p.x);
	}
	else
	{
		if (ray->p.x == floorf(ray->p.x))
			ray->n.x = ray->p.x - 1.f;
		else
			ray->n.x = floor(ray->p.x);
	}
}

void	space(int c_f, t_ray *ray, int x_y)
{
	if (x_y == X_)
	{
		if (c_f == CEIL)
		{
			if (ray->p.y == ceilf(ray->p.y))
				ray->n.y += 1.f;
			else
				ray->n.y = ceilf(ray->p.y);
		}
		if (c_f == FLOOR)
		{
			if (ray->p.y == floorf(ray->p.y))
				ray->n.y -= 1.f;
			else
				ray->n.y = floorf(ray->p.y);
		}
		ray->n.x = ray->p.x;
	}
	if (x_y == Y_)
	{
		if (c_f == CEIL)
		{
			if (ray->p.x == ceilf(ray->p.x))
				ray->n.x += 1.f;
			else
				ray->n.x = ceilf(ray->p.x);
		}
		if (c_f == FLOOR)
		{
			if (ray->p.x == floorf(ray->p.x))
				ray->n.x -= 1.f;
			else
				ray->n.x = floorf(ray->p.x);
		}
		ray->n.y = ray->p.y;
	}
}

void	init_dir(t_ray *r)
{
	if (r->a > 180.f && r->a <= 270.f)
	{
		r->d.x = sinf(deg_to_rad(r->a));
		r->d.y = cosf(deg_to_rad(r->a));
	}
	else if (r->a >= 270.f && r->a <= 360.f)
	{
		r->d.x = -sinf(deg_to_rad(r->a));
		r->d.y = -cosf(deg_to_rad(r->a));
	}
	else if (r->a > 90.f && r->a <= 180.f)
	{
		r->d.x = -sinf(deg_to_rad(r->a));
		r->d.y = -cosf(deg_to_rad(r->a));
	}
	else
	{
		r->d.x = sinf(deg_to_rad(r->a));
		r->d.y = cosf(deg_to_rad(r->a));
	}
}

void	init_dir2(t_ray *r)
{
	t_vecf	dir;

	dir.y = (tan(deg_to_rad(90.f - (FOV / 2.f))) * (SCREEN_W / 2.f));
	dir.x = (r->index * COL_W) - (SCREEN_W / 2);
	// printf("diry %f\n", dir.y);
	// printf("left max %d\n", (0 * COL_W) - (SCREEN_W / 2));
	// printf("index %d\n", r->index);
	r->a = fix_ang(r->a - rad_to_deg(atan2f(dir.y, dir.x)) + 90.f);
	init_dir(r);
} 
void	whey(t_ray *ray)
{
	if (ray->d.x == 0)
	{
		if (ray->d.y > 0)
			space(CEIL, ray, X_);
		else
			space(FLOOR, ray, X_);
		return;
	}
	if (ray->d.y == 0)
	{
		if (ray->d.x > 0)
			space(CEIL, ray, Y_);
		else
			space(FLOOR, ray, Y_);
		return;
	}
	nextt(ray);
	delta(ray);
}
