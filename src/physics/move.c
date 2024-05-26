#include "../../includes/cub3D.h"

float	deg_to_rad(float a)
{
	return (a * PI / 180.0f);
}

int	fix_ang(int a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

void	reset_ecran(t_main *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < SCREEN_H)
	{
		i = 0;
		while (i < SCREEN_W)
		{
			if (y >= (SCREEN_H / 2))
				set_pixel(BLACK_PIXEL, map->img, i, y);
			else
				set_pixel(BLUE_PIXEL, map->img, i, y);
			i++;
		}
		y++;
	}
}

void	s(t_main *map)
{
	int	py;
	int	px;

	px = map->px;
	py = map->py;
	map->py -= map->dy * SPEED;
	map->px += map->dx * SPEED;
	if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
	{
		map->py = py;
		map->px = px;
	}
}

void	w(t_main *map)
{
	int	py;
	int	px;

	px = map->px;
	py = map->py;
	map->py += map->dy * SPEED;
	map->px -= map->dx * SPEED;
	if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
	{
		map->py = py;
		map->px = px;
	}
}

void	a(t_main *map)
{
	float	a;
	int	py;
	int	px;

	px = map->px;
	py = map->py;
	a = fix_ang(map->pa + 90.f);
	map->px += cosf(deg_to_rad(a)) * SPEED;
	map->py -= -sinf(deg_to_rad(a)) * SPEED;
	if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
	{
		map->py = py;
		map->px = px;
	}
}

void	d(t_main *map)
{
	float	a;
	int	py;
	int	px;

	px = map->px;
	py = map->py;
	a = fix_ang(map->pa - 90.f);
	map->px += cosf(deg_to_rad(a)) * SPEED;
	map->py -= -sinf(deg_to_rad(a)) * SPEED;
	if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
	{
		map->py = py;
		map->px = px;
	}
}

void	arrows1(t_main *map)
{
	map->pa += 10;
	map->pa = fix_ang(map->pa);
	map->dx = cosf(deg_to_rad(map->pa));
	map->dy = -sinf(deg_to_rad(map->pa));
}

void	arrows2(t_main *map)
{
	map->pa -= 10;
	map->pa = fix_ang(map->pa);
	map->dx = cosf(deg_to_rad(map->pa));
	map->dy = -sinf(deg_to_rad(map->pa));
}

int	move(int key, t_main *map)
{
	if (key == 's')
		s(map);
	if (key == 'd')
		d(map);
	if (key == 'w')
		w(map);
	if (key == 'a')
		a(map);
	if (key == 65363)
		arrows1(map);
	if (key == 65361)
		arrows2(map);
	if (key == 65307)
		on_destroy(map);
	//print_map(map);
	reset_ecran(map);
	put_(map);
	return (1);
}
