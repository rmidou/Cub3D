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
	main->scr.data = mlx_get_data_addr(main->scr.img, &(main->scr.bpp), &(main->scr.line), &(main->scr.endian));
	main->dx = cos(deg_to_rad(main->pa));
	main->dy = -sin(deg_to_rad(main->pa));
	if (build_map(main->mlxptr, &(main->map), av[1]) != OKAY_OKAY)
		on_destroy(main);
	main->px = main->map.spawn.x;
	main->py = main->map.spawn.y;
	main->pa = main->map.view;
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
