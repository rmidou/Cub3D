#include "../includes/cub3D.h"

#include <stdio.h>
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

	map->x = 0;
	map->y = 500;
	y = 0;
	i = 0;
	while (y < 10)
	{
		i = 0;
		while (i < 34)
		{
			map->x = i;
			map->y = y + 10;
			if (map->y >= 15)
				put_img('1', *map);
			else
				put_img('2', *map);
			i++;
		}
		y++;
	}
}

int	move(int key, t_main *map)
{
	int	py;
	int	px;

	if (key == 's')
	{
		px = map->px;
		py = map->py;
		map->py -= map->dy * 10;
		map->px += map->dx * 10;
		if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
		{
			map->py = py;
			map->px = px;
		}
	}
	if (key == 'd')
	{
		map->pa += 10;
		map->pa = fix_ang(map->pa);
		map->dx = cos(deg_to_rad(map->pa));
		map->dy = -sin(deg_to_rad(map->pa));
	}
	if (key == 'w')
	{
		px = map->px;
		py = map->py;
		map->py += map->dy * 10;
		map->px -= map->dx * 10;
		if (map->map[(int)round(map->py/64)][(int)round(map->px/64)] == '1')
		{
			map->py = py;
			map->px = px;
		}
	}
	if (key == 'a')
	{
		map->pa -= 10;
		map->pa = fix_ang(map->pa);
		map->dx = cos(deg_to_rad(map->pa));
		map->dy = -sin(deg_to_rad(map->pa));
	}
	if (key == 65307)
		on_destroy(map);
	print_map(map);
	reset_ecran(map);
	put_(map);
	return (1);
}
