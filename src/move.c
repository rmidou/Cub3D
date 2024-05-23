/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:43:30 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/23 20:44:33 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
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

int	move(int key, t_main *map)
{
	if (key == 's')
	{
		map->py -= map->dy * 10;
		map->px += map->dx * 10;
	}
	if (key == 'd')
	{
		map->pa += 10;
		map->pa = fix_ang(map->pa);
		map->dx = cos(deg_to_rad(map->pa));
		map->dy = -sin(deg_to_rad(map->pa));
	}
	if (key == 'w')
	{
		map->py += map->dy * 10;
		map->px -= map->dx * 10;
	}
	if (key == 'a')
	{
		map->pa -= 10;
		map->pa = fix_ang(map->pa);
		map->dx = cos(deg_to_rad(map->pa));
		map->dy = -sin(deg_to_rad(map->pa));
	}
	if (key == 65307)
		on_destroy(map);
	print_map(map);
	put_(map);
	return (1);
}
