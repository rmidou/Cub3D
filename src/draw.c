/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:54:36 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/25 13:55:36 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_pixel(t_game g, int x, int y, char *val)
{
	float	light;

	light = add_dithering(get_lighting(g, x, y), x, y);
	if (light > 1.f)
		light = 1.f;
	g.data[y * g.line + x * (g.bpp / 8) + 0]
		= (float)(unsigned char)val[0] * light;
	g.data[y * g.line + x * (g.bpp / 8) + 1]
		= (float)(unsigned char)val[1] * light;
	g.data[y * g.line + x * (g.bpp / 8) + 2]
		= (float)(unsigned char)val[2] * light;
}

char	*get_pix(t_tex t, int x, int y)
{
	return (&(t.data[y * t.line + x * (t.bpp / 8)]));
}

void	clear_screen(t_game g)
{
	ft_memset(g.data, 0, g.size.x * g.size.y * (g.bpp / 8));
}

char	*get_pix2(t_game g, int x, int y)
{
	return (&(g.data[y * g.line + x * (g.bpp / 8)]));
}

int	pixel_cmp(char *p1, char *p2)
{
	return (p1[0] == p2[0]
		&& p1[1] == p2[1]
		&& p1[2] == p2[2]);
}
