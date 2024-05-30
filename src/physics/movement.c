#include "../../includes/cub3D.h"

void	move_ang(t_main *main, float a)
{
	t_vecf	mv;

	mv = ang_to_vecf(fix_ang(a + main->plr.a));
	mv = scale(mv, SPEED);
	if (get_block2(main, add(main->plr.p, mv)) != '1')
		main->plr.p = add(main->plr.p, mv);
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
	if (key == 'w')
		move_ang(main, 0);
	if (key == 's')
		move_ang(main, 180);
	if (key == 'a')
		move_ang(main, 270);
	if (key == 'd')
		move_ang(main, 90);
	if (key == 65363)
		arrows1(main);
	if (key == 65361)
		arrows2(main);
	if (key == 65307)
		on_destroy(main);
	reset_screen(main);
	shoot_rays(main);
	return (1);
}