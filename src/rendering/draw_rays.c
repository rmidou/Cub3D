#include "../../includes/cub3D.h"

void	draw_3d(t_main *main, int x, t_ray r)
{
	int		i;
	t_clr	c;
	float	len;

	i = x;
	len = get_line_height(main, r);
	c = get_hit_color(main, r);
	while (i < x + COL_W)
	{
		draw_line(main,
			(t_veci){i, (SCREEN_H / 2) - len / 2},
			(t_veci){i, (SCREEN_H / 2) + len / 2},
			c.color_i);
		i++;
	}
}

char	get_block(t_main *main, t_ray r)
{
	t_veci	i;

	i.x = (int)floorf(r.p.x);
	i.y = (int)floorf(r.p.y);
	if (r.p.x == floorf(r.p.x) && r.d.x < .0f)
		i.x--;
	if (r.p.y == floorf(r.p.y) && r.d.y < .0f)
		i.y--;
	if (i.y < 0.f || i.y >= main->map.size.y
		|| i.x < 0.f || i.x >= main->map.size.x)
		return ('1');
	return (main->map.map[i.y][i.x]);
}

int	out_of_bounds(t_main *main, t_vecf p)
{
	if (p.x < 0.f || p.x > main->map.size.x
		|| p.y < 0.f || p.y > main->map.size.y)
		return (0);
	return (1);
}

void	get_hit(t_ray *r)
{
	if (r->p.x == floorf(r->p.x) && r->d.x < 0.f)
		r->hit = HIT_E;
	else if (r->p.x == floorf(r->p.x))
		r->hit = HIT_W;
	else if (r->p.y == floorf(r->p.y) && r->d.y < 0.f)
		r->hit = HIT_N;
	else
		r->hit = HIT_S;
}

void	shoot_rays(t_main *main)
{
	int		col_index;
	t_ray	r;

	col_index = -1;
	while (++col_index < (SCREEN_W / COL_W))
	{
		r.a = fix_ang(main->plr.a);
		r.index = col_index;
		init_dir2(&r);
		r.p.x = main->plr.p.x;
		r.p.y = main->plr.p.y;
		while (out_of_bounds(main, r.p) && get_block(main, r) != '1')
		{
			whey(&r);
			r.p = r.n;
		}
		get_hit(&r);
		if (out_of_bounds(main, r.p))
			draw_3d(main, col_index * COL_W, r);
	}
	mini_map(main);
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->scr.img, 0, 0);
}
