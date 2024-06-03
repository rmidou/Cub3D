/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:59 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:54:59 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	door_remove(t_main *m)
{
	int	x;
	int	y;

	y = 0;
	while (m->map.map[y])
	{
		x = 0;
		while (m->map.map[y][x])
		{
			if (m->map.map[y][x] == 'D')
				m->map.map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	update_textures(t_anim *t)
{
	t->frame = (t->frame + 1) % t->size;
}

int	init_animation(t_anim *t, int frames)
{
	t->txrs = malloc(sizeof(t_txr) * frames);
	ft_bzero(t->txrs, sizeof(t_txr) * frames);
	t->size = frames;
	return (1);
}

void	init_texture(t_main *m)
{
	init_animation(&m->map.n, 1);
	init_animation(&m->map.s, 1);
	init_animation(&m->map.e, 1);
	init_animation(&m->map.w, 1);
	init_animation(&m->map.d, 4);
	m->map.d.frame = 0;
	m->map.d.txrs[0].file = "textures/door.xpm";
	m->map.d.txrs[1].file = "textures/door2.xpm";
	m->map.d.txrs[2].file = "textures/door3.xpm";
	m->map.d.txrs[3].file = "textures/door4.xpm";
	load_tex(m->mlxptr, &m->map.d.txrs[0]);
	load_tex(m->mlxptr, &m->map.d.txrs[1]);
	load_tex(m->mlxptr, &m->map.d.txrs[2]);
	load_tex(m->mlxptr, &m->map.d.txrs[3]);
}
