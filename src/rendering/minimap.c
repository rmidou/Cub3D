#include "../../includes/cub3D.h"

void	print_player(t_main *main, int scale)
{
	int	x;
	int	y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			set_pixel(RED_PIXEL, main->scr, main->plr.p.x * scale + x,
				main->plr.p.y * scale + y);
			y++;
		}
		x++;
	}
}

int	ft_scale(t_main *main)
{
	int	max_map_dimension;
	int	minimap_size;
	int	scale;

	if (main->map.size.x > main->map.size.y)
		max_map_dimension = main->map.size.x;
	else
		max_map_dimension = main->map.size.y;
	minimap_size = SCREEN_W / 3;
	scale = minimap_size / max_map_dimension;
	return (scale);
}

void	print_mini_map(t_main *main, char c, int yy, int ii)
{
	int	x;
	int	scale;
	int	y;
	int	color;

	scale = ft_scale(main);
	x = 1;
	while (x <= scale)
	{
		y = 1;
		while (y <= scale)
		{
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				color = WHITE_PIXEL;
			else if (c == 'D')
				color = BLUE_PIXEL;
			else
				color = BLACK_PIXEL;
			set_pixel(color, main->scr, x + ii * scale, y + yy * scale);
			y++;
		}
		x++;
	}
	print_player(main, scale);
}

// FAIRE UN CURSEUR

void	mini_map(t_main *main)
{
	int	x;
	int	y;

	y = 0;
	while (y < main->map.size.y)
	{
		x = 0;
		while (x < main->map.size.x)
		{
			print_mini_map(main, get_block2(main, vecf(x, y)), y, x);
			x++;
		}
		y++;
	}
}
