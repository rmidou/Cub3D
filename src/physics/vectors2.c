/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:56 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:54:56 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_vecf	scale(t_vecf v, float f)
{
	return (vecf(v.x * f, v.y * f));
}

int	get_line_height(t_main *m)
{
	t_vecf	ray_path;
	float	len;

	ray_path = sub(m->ray.p, m->plr.p);
	ray_path = rotate(ray_path, -(m->plr.a));
	len = abs((int)((tanf(to_rad(90.f - (FOV / 2.f))) * SCREEN_W)
				/ (2.f * ray_path.x)));
	return (len);
}

float	absf(float f)
{
	if (f < 0.f)
		return (-f);
	return (f);
}
