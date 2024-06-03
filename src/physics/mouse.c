/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:50 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 14:01:44 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse(int x, int y, t_main *m)
{
	float	s;

	mlx_mouse_hide(m->mlxptr, m->winptr);
	if ((m->mouse.x - x) == 0)
		return (0);
	s = 1.f;
	if ((m->mouse.x - x) > 0.f)
		s = -1.f;
	m->plr.a += s * MOUSE_SPEED;
	m->plr.a = fix_ang(m->plr.a);
	m->mouse.x = x;
	m->mouse.y = y;
	m->update = 1;
	return (0);
}
