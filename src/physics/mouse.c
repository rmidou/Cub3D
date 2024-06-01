#include "../../includes/cub3D.h"

int	mouse(int x, int y, t_main *m)
{
	float	s;

	if ((m->mouse.x - x) == 0)
		return (0);
	s = 1.f;
	if ((m->mouse.x - x) > 0.f)
		s = -1.f;
	m->plr.a += s * MOUSE_SPEED;
	m->plr.a = fix_ang(m->plr.a);
	//printf("moved %f; angle = %f\n", s * MOUSE_SPEED, m->plr.a);
	//mlx_mouse_move(m->mlxptr, m->winptr, SCREEN_W / 2, SCREEN_H / 2);
	m->mouse.x = x;
	m->mouse.y = y;
	m->update = 1;
	return (0);
}