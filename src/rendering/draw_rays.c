/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:55:03 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:55:03 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_3d(t_main *main, int x, t_ray r)
{
	int		i;
	t_clr	c;
	float	len;

	i = x;
	len = get_line_height(main);
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

char	get_block(t_main *main)
{
	t_veci	i;

	i.x = (int)floorf(main->ray.p.x);
	i.y = (int)floorf(main->ray.p.y);
	if (main->ray.p.x == floorf(main->ray.p.x) && main->ray.d.x < .0f)
		i.x--;
	if (main->ray.p.y == floorf(main->ray.p.y) && main->ray.d.y < .0f)
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
		r->hit = HIT_S;
	else
		r->hit = HIT_N;
}

void	shoot_rays(t_main *main)
{
	int		col_index;

	col_index = -1;
	while (++col_index < (SCREEN_W / COL_W))
	{
		main->ray.a = fix_ang(main->plr.a);
		main->ray.index = col_index;
		init_dir2(&main->ray);
		main->ray.p.x = main->plr.p.x;
		main->ray.p.y = main->plr.p.y;
		while (out_of_bounds(main, main->ray.p) && (get_block(main) != '1'
				&& get_block(main) != 'D'))
		{
			whey(&main->ray);
			main->ray.p = main->ray.n;
		}
		if (get_block(main) != 'D')
			get_hit(&main->ray);
		else
			main->ray.hit = HIT_D;
		if (out_of_bounds(main, main->ray.p))
			draw_texture(main, col_index * COL_W);
	}
	mini_map(main);
	mlx_put_image_to_window(main->mlxptr, main->winptr, main->scr.img, 0, 0);
}
