/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:55:05 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:55:05 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_pixel(int color, t_txr t, int x, int y)
{
	int		pixel;

	if (x < 0 || x >= t.size.x || y < 0 || y >= t.size.y)
		return ;
	pixel = (y * t.line) + (x * (t.bpp / 8));
	if (t.endian == 1)
	{
		t.data[pixel + 0] = (color >> 24);
		t.data[pixel + 1] = (color >> 16) & 0xFF;
		t.data[pixel + 2] = (color >> 8) & 0xFF;
		t.data[pixel + 3] = (color) & 0xFF;
	}
	else if (t.endian == 0)
	{
		t.data[pixel + 0] = (color) & 0xFF;
		t.data[pixel + 1] = (color >> 8) & 0xFF;
		t.data[pixel + 2] = (color >> 16) & 0xFF;
		t.data[pixel + 3] = (color >> 24);
	}
}

t_clr	get_pixel(t_txr t, int x, int y)
{
	int		pixel;

	if (x < 0 || x >= t.size.x || y < 0 || y >= t.size.y)
		return (color(255, 0, 0));
	pixel = (y * t.line) + (x * (t.bpp / 8));
	return (color(t.data[pixel + 2],
			t.data[pixel + 1],
			t.data[pixel + 0]));
}

void	draw_line(t_main *main, t_veci start, t_veci end, int color)
{
	int		i;
	int		steps;
	t_veci	d;
	t_vecf	inc;
	t_veci	pos;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = abs(d.y);
	if (abs(d.x) > abs(d.y))
		steps = abs(d.x);
	inc.x = d.x / (float)steps;
	inc.y = d.y / (float)steps;
	pos.x = start.x;
	pos.y = start.y;
	i = 0;
	while (i <= steps)
	{
		set_pixel(color, main->scr, round(pos.x), round(pos.y));
		pos.x += inc.x;
		pos.y += inc.y;
		i++;
	}
}

float	get_shade(int y)
{
	float	len;
	float	x;
	float	shade;

	len = (float)abs(y - ((int)SCREEN_H / 2)) * 2.f;
	if (len == 0.f)
		return (0.f);
	x = (tanf(to_rad(90.f - (FOV / 2.f))) * SCREEN_W) / (2.f * len);
	shade = 1.f - (1.f / (RENDER_DIST / x));
	if (shade < -.25f)
		shade = -.25f;
	return (shade);
}

void	reset_screen(t_main *main)
{
	int		y;
	int		x;
	float	l;

	y = 0;
	x = 0;
	while (y < SCREEN_H)
	{
		l = get_shade(y) + .25f;
		x = 0;
		while (x < SCREEN_W)
		{
			if (y >= (SCREEN_H / 2))
				set_pixel(scale_clr(main->map.floor,
						add_dithering(l, x, y)).color_i, main->scr, x, y);
			if (y < (SCREEN_H / 2))
				set_pixel(scale_clr(main->map.ceiling,
						add_dithering(l, x, y)).color_i, main->scr, x, y);
			x++;
		}
		y++;
	}
}
