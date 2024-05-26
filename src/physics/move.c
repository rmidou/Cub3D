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
				set_pixel(main->map.floor.color_i, main->scr, i, y);
			if (y < (SCREEN_H / 2))
				set_pixel(main->map.ceiling.color_i, main->scr, i, y);
			i++;
		}
		y++;
	}
}

void	s(t_main *main)
{
	float	py;
	float	px;

	px = main->plr.p.x;
	py = main->plr.p.y;
	main->plr.p.x -= cosf(deg_to_rad(main->plr.a)) * SPEED;
	main->plr.p.y -= sinf(deg_to_rad(main->plr.a)) * SPEED;
	if (main->map.map[(int)round(main->plr.p.y)][(int)round(main->plr.p.x)] == '1')
	{
		main->plr.p.y = py;
		main->plr.p.x = px;
	}
}

void	w(t_main *main)
{
	float	py;
	float	px;

	px = main->plr.p.x;
	py = main->plr.p.y;
	main->plr.p.x += cosf(deg_to_rad(main->plr.a)) * SPEED;
	main->plr.p.y += sinf(deg_to_rad(main->plr.a)) * SPEED;
	if (main->map.map[(int)round(main->plr.p.y)][(int)round(main->plr.p.x)] == '1')
	{
		main->plr.p.y = py;
		main->plr.p.x = px;
	}
}

void	a(t_main *main)
{
	float	a;
	float	py;
	float	px;

	px = main->plr.p.x;
	py = main->plr.p.y;
	a = fix_ang(main->plr.a + 90.f);
	main->plr.p.x += cosf(deg_to_rad(a)) * SPEED;
	main->plr.p.y -= -sinf(deg_to_rad(a)) * SPEED;
	if (main->map.map[(int)round(main->plr.p.y)][(int)round(main->plr.p.x)] == '1')
	{
		main->plr.p.y = py;
		main->plr.p.x = px;
	}
}

void	d(t_main *main)
{
	float	a;
	float	py;
	float	px;

	px = main->plr.p.x;
	py = main->plr.p.y;
	a = fix_ang(main->plr.a - 90.f);
	main->plr.p.x += cosf(deg_to_rad(a)) * SPEED;
	main->plr.p.y -= -sinf(deg_to_rad(a)) * SPEED;
	if (main->map.map[(int)round(main->plr.p.y)][(int)round(main->plr.p.x)] == '1')
	{
		main->plr.p.y = py;
		main->plr.p.x = px;
	}
}

void	arrows1(t_main *main)
{
	main->plr.a += 10;
	main->plr.a = fix_ang(main->plr.a);
}

void	arrows2(t_main *main)
{
	main->plr.a -= 10;
	main->plr.a = fix_ang(main->plr.a);
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
	reset_ecran(main);
	draw_view_line(main);
	return (1);
}
