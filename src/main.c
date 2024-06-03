/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:55:15 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 14:01:57 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	on_destroy(t_main *main)
{
	free_map(main->mlxptr, &(main->map));
	mlx_destroy_image(main->mlxptr, main->scr.img);
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
	main->map.door = 0;
	main->map.ceiling = color(-1, -1, -1);
	main->map.floor = color(-1, -1, -1);
	init_texture(main);
	if (build_map(main->mlxptr, &(main->map), av[1], main) != OKAY_OKAY)
		on_destroy(main);
	main->plr.p.x = main->map.spawn.x + .5f;
	main->plr.p.y = main->map.spawn.y + .5f;
	main->plr.a = main->map.view;
	main->update = 1;
}

int	loop(t_main *m)
{
	static int	compteur = 0;

	compteur++;
	if (compteur % NB_FRAME == 0)
	{
		if (m->map.door == 1 && m->map.d.frame != m->map.d.size - 1)
			update_textures(&m->map.d);
		else if (m->map.door == 1)
		{
			m->map.door = 0;
			door_remove(m);
		}
	}
	reset_screen(m);
	shoot_rays(m);
	m->update = 0;
	return (0);
}

int	verif_cub(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (i > 3 && av[i - 1] == 'b' && av[i - 2] == 'u'
		&& av[i - 3] == 'c' && av[i - 4] == '.')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;
	int		fd;

	fd = -1;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (throw_error(ERR_ARG, NULL));
	if (fd < 0)
		return (throw_error(ERR_OPEN, av[1]));
	if (verif_cub(av[1]) == 0)
		return (throw_error(ERR_EXT, NULL));
	close(fd);
	init(&main, av);
	mlx_hook(main.winptr, KeyRelease, KeyReleaseMask, &move, &main);
	if (MOUSE)
		mlx_hook(main.winptr, 6, 64, &mouse, &main);
	mlx_hook(main.winptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &main);
	mlx_loop_hook(main.mlxptr, &loop, &main);
	mlx_loop(main.mlxptr);
	return (0);
}
