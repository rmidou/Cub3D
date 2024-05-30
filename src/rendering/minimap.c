#include "../../includes/cub3D.h"

void	print_player(t_main *main, int scale)
{
	set_pixel(RED_PIXEL, main->scr, main->plr.p.x * scale, main->plr.p.y * scale);
	set_pixel(RED_PIXEL, main->scr, (main->plr.p.x * scale) + 1, (main->plr.p.y * scale) + 1);
	set_pixel(RED_PIXEL, main->scr, (main->plr.p.x * scale) + 1, main->plr.p.y * scale);
	set_pixel(RED_PIXEL, main->scr, main->plr.p.x * scale, (main->plr.p.y * scale) + 1);
}

void	print_mini_map(t_main *main, char c, int yy, int ii)
{
	int	x;
	int scale;
	int	y;
	int	color;

	scale = (SCREEN_W / 5) / (main->map.size.x > main->map.size.y ? main->map.size.x : main->map.size.y);
	x = 1;
	while (x < scale)
	{
		y = 1;
		while (y < scale)
		{
			if (c == '0' || c == 'N')
				color = WHITE_PIXEL;
			else
				color = BLACK_PIXEL;
			set_pixel(color, main->scr, x + ii * scale, y + yy * scale);
			y++;
		}
		x++;
	}
	print_player(main, scale);
}

void	mini_map(t_main *main)
{
	int	i;
	int	y;

	y = 0;
	while (main->map.map[y])
	{
		i = 0;
		while (main->map.map[y][i])
		{
			print_mini_map(main, main->map.map[y][i], y, i);
			i++;
		}
		y++;
	}
}