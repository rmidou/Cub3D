/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 08:37:52 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/25 13:35:25 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int    draw_line(t_main *main, int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	int	tt;

	tt = 0;
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(main->mlxptr, main->winptr, x0, y0, color);
		// voir le so long de jules
		tt += 1;
	    if (x0 == x1 && y0 == y1)
			break;
	    e2 = 2 * err;
	    if (e2 >= dy)
		{
	        err += dy;
	        x0 += sx;
	    }
	    if (e2 <= dx)
		{
	        err += dx;
	        y0 += sy;
	    }
	}
	return (tt);
}

void	draw_3D(t_main *main, int x, float len)
{
	int	i;
	float height;
	float dist_screen = 32.f;

	i = x;
	//len = (64 * 640) / len;
	height = (dist_screen / len) * 32.f * 64.f;
	len = height;
	if (len > 640)
		len = 640;
	while (i < x + 2)
	{
		draw_line(main, i, 960 - len / 2, i, 960 + len / 2, RED_PIXEL);
		i++;
	}
}

void    draw_view_line(t_main *main)
{
	int line_length;
	int x1;
	int y1;
	float	para;
	//int	tt;
	//int	ca;

	para = -45.f;
	while (para <= 45.f)
	{
		line_length = 1;
		x1 = main->px + cosf(deg_to_rad(main->pa + para) - PI);
		y1 = main->py + sinf(deg_to_rad(main->pa + para) - PI);
		while (main->map[(int)round(y1/64)][(int)round(x1/64)] != '1')
		{
			line_length++;
			x1 = main->px + (cosf(deg_to_rad(main->pa + para) - PI) * line_length);
			y1 = main->py + (sinf(deg_to_rad(main->pa + para) - PI) * line_length);
		}
		draw_line(main, main->px, main->py, x1, y1, RED_PIXEL);
		//ca = fix_ang(main->pa - (main->pa + para));
		draw_3D(main, (para + 30.f) * 33.f, sqrtf(powf(x1 - main->px, 2) + powf(y1 - main->py, 2)));
		para+= 0.05f;
	}
}
