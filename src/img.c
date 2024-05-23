/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:28:06 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/23 20:38:19 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_img_2(int color, void *colorr)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
	int		y;
	int		x;
	int		pixel;

	buffer = mlx_get_data_addr(colorr, &pixel_bits, &line_bytes, &endian);
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			pixel = (y * line_bytes) + (x * (pixel_bits / 8));
			if (endian == 1)
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color) & 0xFF;
			}
			else if (endian == 0)
			{
				buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
				buffer[pixel + 3] = (color >> 24);
			}
			x++;
		}
		y++;
	}
}

void	init_img(t_main *map)
{
	map->black = mlx_new_image(map->mlxptr, 64, 64);
	init_img_2(BLACK_PIXEL, map->black);
	map->white = mlx_new_image(map->mlxptr, 64, 64);
	init_img_2(WHITE_PIXEL, map->white);
}

void	put_img(char chara, t_main map)
{
	if (chara == '1')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.black, map.x * 64, map.y * 64);
	if (chara == '0')
		mlx_put_image_to_window
			(map.mlxptr, map.winptr, map.white, map.x * 64, map.y * 64);
}

void	put_(t_main *map)
{
	int	i;
	int	y;

	i = map->px;
	map->px = map->px;
	map->py = map->py;
	while (i < map->px + 10)
	{
		mlx_pixel_put(map->mlxptr, map->winptr, i, map->py, RED_PIXEL);
		y = map->py;
		while (y < map->py + 10)
		{
			mlx_pixel_put(map->mlxptr, map->winptr, i, y, RED_PIXEL);
			y++;
		}
		i++;
	}
}
