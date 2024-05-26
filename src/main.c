#include "../includes/cub3D.h"

int	on_destroy(t_main *map)
{
	mlx_destroy_window(map->mlxptr, map->winptr);
	mlx_destroy_image(map->mlxptr, map->black);
	mlx_destroy_image(map->mlxptr, map->white);
	mlx_destroy_display(map->mlxptr);
	free(map->mlxptr);
	free_map(map);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	map;

	if (ac < 2)
		return (0);
	map.mlxptr = mlx_init();
	build_map(map.mlxptr, map.map, "maps/map_subject.cub");
	map.winptr = mlx_new_window(map.mlxptr, SCREEN_W, SCREEN_H, "cub3D");
	map.img = mlx_new_image(map.mlxptr, SCREEN_W, SCREEN_H);
	map.px = 150;
	map.py = 400;
	map.pa = 90;
	map.dx = cos(deg_to_rad(map.pa));
	map.dy = -sin(deg_to_rad(map.pa)); 
	read_map(&map, av[1]);
	init_img(&map);
	mlx_hook(map.winptr, KeyRelease, KeyReleaseMask, &move, &map);
	mlx_hook(map.winptr, DestroyNotify, StructureNotifyMask, &on_destroy, &map);
	mlx_loop(map.mlxptr);
	return (0);
}
