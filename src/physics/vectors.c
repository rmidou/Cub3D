/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:54 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:54:54 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_vecf	vecf(float x, float y)
{
	return ((t_vecf){x, y});
}

float	dist(t_vecf v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vecf	norm(t_vecf v)
{
	float	len;

	len = dist(v);
	return (vecf(v.x / len, v.y / len));
}

t_vecf	add(t_vecf u, t_vecf v)
{
	return (vecf(u.x + v.x, u.y + v.y));
}

t_vecf	sub(t_vecf u, t_vecf v)
{
	return (vecf(u.x - v.x, u.y - v.y));
}
