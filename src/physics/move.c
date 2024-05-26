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

void	reset_ecran(t_main *main)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	ft_bzero(main->scr.data, SCREEN_W * SCREEN_H * (main->scr.bpp / 8));
	while (y < SCREEN_H)
	{
		i = 0;
		while (i < SCREEN_W)
		{
			if (y >= (SCREEN_H / 2))
				set_pixel(main->map.floor.color_i, main->scr.img, i, y);
			if (y < (SCREEN_H / 2))
				set_pixel(main->map.ceiling.color_i, main->scr.img, i, y);
			i++;
		}
		y++;
	}
}

void	s(t_main *main)
{
	int	py;
	int	px;

	px = main->px;
	py = main->py;
	main->py -= main->dy * SPEED;
	main->px += main->dx * SPEED;
	if (main->map.map[(int)round(main->py/64)][(int)round(main->px/64)] == '1')
	{
		main->py = py;
		main->px = px;
	}
}

void	w(t_main *main)
{
	int	py;
	int	px;

	px = main->px;
	py = main->py;
	main->py += main->dy * SPEED;
	main->px -= main->dx * SPEED;
	if (main->map.map[(int)round(main->py/64)][(int)round(main->px/64)] == '1')
	{
		main->py = py;
		main->px = px;
	}
}

void	a(t_main *main)
{
	float	a;
	int	py;
	int	px;

	px = main->px;
	py = main->py;
	a = fix_ang(main->pa + 90.f);
	main->px += cosf(deg_to_rad(a)) * SPEED;
	main->py -= -sinf(deg_to_rad(a)) * SPEED;
	if (main->map.map[(int)round(main->py/64)][(int)round(main->px/64)] == '1')
	{
		main->py = py;
		main->px = px;
	}
}

void	d(t_main *main)
{
	float	a;
	int	py;
	int	px;

	px = main->px;
	py = main->py;
	a = fix_ang(main->pa - 90.f);
	main->px += cosf(deg_to_rad(a)) * SPEED;
	main->py -= -sinf(deg_to_rad(a)) * SPEED;
	if (main->map.map[(int)round(main->py/64)][(int)round(main->px/64)] == '1')
	{
		main->py = py;
		main->px = px;
	}
}

void	arrows1(t_main *main)
{
	main->pa += 10;
	main->pa = fix_ang(main->pa);
	main->dx = cosf(deg_to_rad(main->pa));
	main->dy = -sinf(deg_to_rad(main->pa));
}

void	arrows2(t_main *main)
{
	main->pa -= 10;
	main->pa = fix_ang(main->pa);
	main->dx = cosf(deg_to_rad(main->pa));
	main->dy = -sinf(deg_to_rad(main->pa));
}

int	move(int key, t_main *main)
{
	if (key == 's')
		s(main);
	if (key == 'd')
		d(main);
	if (key == 'w')
		w(main);
	if (key == 'a')
		a(main);
	if (key == 65363)
		arrows1(main);
	if (key == 65361)
		arrows2(main);
	if (key == 65307)
		on_destroy(main);
	//print_map(map);
	reset_ecran(main);
	draw_view_line(main);
	return (1);
}
