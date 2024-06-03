/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:55:12 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:55:12 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_texture(t_main *m, int x_pos)
{
	int		y;
	float	len;
	t_txr	t;

	len = get_line_height(m);
	t = get_hit_texture(m, m->ray);
	y = -1;
	while (++y < (int)len)
	{
		if ((SCREEN_H / 2) + (y - (len / 2)) < 0
			|| (SCREEN_H / 2) + (y - (len / 2)) > SCREEN_H)
			continue ;
		draw_row(m, (t_veci){x_pos, y}, t, len);
	}
}
