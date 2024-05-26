#include "../includes/cub3D.h"

int	on_destroy(t_main *main)
{
	mlx_destroy_window(main->mlxptr, main->winptr);
	mlx_destroy_display(main->mlxptr);
	free(main->mlxptr);
	free_map(main);
	exit(0);
	return (0);
}

void	init(t_main *main, char **av)
{
	main->mlxptr = mlx_init();
	main->winptr = mlx_new_window(main->mlxptr, SCREEN_W, SCREEN_H, "cub3D");
	main->scr.img = mlx_new_image(main->mlxptr, SCREEN_W, SCREEN_H);
	main->scr.data = mlx_get_data_addr(main->scr.img, &(main->scr.bpp), &(main->scr.line), &(main->scr.endian));
	main->px = 150;
	main->py = 400;
	main->pa = 90;
	main->dx = cos(deg_to_rad(main->pa));
	main->dy = -sin(deg_to_rad(main->pa));
	build_map(main->mlxptr, &(main->map), av[1]);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 2)
		return (0);
	init(&main, av);
	mlx_hook(main.winptr, KeyRelease, KeyReleaseMask, &move, &main);
	mlx_hook(main.winptr, DestroyNotify, StructureNotifyMask, &on_destroy, &main);
	mlx_loop(main.mlxptr);
	return (0);
}
