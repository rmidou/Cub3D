/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 08:37:52 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/24 16:50:25 by rmidou           ###   ########.fr       */
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

void	draw_3D(t_main *main, int x, int len)
{
	int	i;

	i = x;
	len = (64 * 500) / len;
	if (len > 500)
		len = 500;
	while (i < x + 33)
	{
		draw_line(main, i, 750 - len / 2, i, 750 + len / 2, RED_PIXEL);
		i++;
	}
}

void    draw_view_line(t_main *main)
{
	int line_length;
	int x1;
	int y1;
	int	para;
	int	tt;
	int	ca;

	para = -30;
	while (para != 30)
	{
		line_length = 1;
		x1 = main->px + cos(deg_to_rad(main->pa + para) - M_PI);
		y1 = main->py + sin(deg_to_rad(main->pa + para) - M_PI);
		while (main->map[(int)round(y1/64)][(int)round(x1/64)] != '1')
		{
			line_length++;
			x1 = main->px + (cos(deg_to_rad(main->pa + para) - M_PI) * line_length);
			y1 = main->py + (sin(deg_to_rad(main->pa + para) - M_PI) * line_length);
		}
		tt = draw_line(main, main->px, main->py, x1, y1, RED_PIXEL);
		ca = fix_ang(main->pa - (main->pa + para));
		draw_3D(main, (para + 30) * 33, tt * cos(deg_to_rad(ca)));
		para++;
	}
}
