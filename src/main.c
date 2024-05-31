#include "../includes/cub3D.h"

int	on_destroy(t_main *main)
{
	free_main(main);
	mlx_destroy_window(main->mlxptr, main->winptr);
	mlx_destroy_display(main->mlxptr);
	free(main->mlxptr);
	ft_bzero(main, sizeof(t_main));
	exit(0);
	return (0);
}

void	init(t_main *main, char **av)
{
	ft_bzero(main, sizeof(t_main));
	main->mlxptr = mlx_init();
	main->winptr = mlx_new_window(main->mlxptr, SCREEN_W, SCREEN_H, "cub3d");
	main->scr.img = mlx_new_image(main->mlxptr, SCREEN_W, SCREEN_H);
	main->scr.data = mlx_get_data_addr(main->scr.img, &(main->scr.bpp),
			&(main->scr.line), &(main->scr.endian));
	main->scr.size = (t_veci){SCREEN_W, SCREEN_H};
	if (build_map(main->mlxptr, &(main->map), av[1]) != OKAY_OKAY)
		on_destroy(main);
	main->plr.p.x = main->map.spawn.x + .5f;
	main->plr.p.y = main->map.spawn.y + .5f;
	main->plr.a = main->map.view;
	main->update = 1;
}

int	loop(t_main *m)
{
	if (m->update == 0)
		return (0);
	reset_screen(m);
	shoot_rays(m);
	m->update = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 2)
		return (0);
	init(&main, av);
	mlx_hook(main.winptr, KeyRelease, KeyReleaseMask, &move, &main);
	mlx_hook(main.winptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &main);
	mlx_loop_hook(main.mlxptr, &loop, &main);
	mlx_loop(main.mlxptr);
	return (0);
}
