#include "../../includes/cub3D.h"

void	fill_block_pos(t_main *m, t_vecf blocks[9])
{
	blocks[0] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f, .y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[1] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f, .y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[2] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f, .y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[3] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f, .y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[4] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f, .y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[5] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f, .y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[6] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f, .y = floorf(m->plr.p.y + 1.f) + .5f};
	blocks[7] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f, .y = floorf(m->plr.p.y + 1.f) + .5f};
	blocks[8] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f, .y = floorf(m->plr.p.y + 1.f) + .5f};
}

void	clip_x(t_main *m, t_vecf block)
{
	t_vecf	mv;

	mv.y = 0;
	if (sub(block, m->plr.p).x < 0)
		mv.x = COLLISION_DIST - absf(sub(block, m->plr.p).x);
	else
		mv.x = -(COLLISION_DIST - absf(sub(block, m->plr.p).x));
	if (get_block2(m, add(m->plr.p, mv)) == '1')
		clip_y(m, block);
	else
		m->plr.p = add(m->plr.p, mv);
}

void	clip_y(t_main *m, t_vecf block)
{
	t_vecf	mv;

	mv.x = 0;
	if (sub(block, m->plr.p).y < 0)
		mv.y = COLLISION_DIST - absf(sub(block, m->plr.p).y);
	else
		mv.y = -(COLLISION_DIST - absf(sub(block, m->plr.p).y));
	if (get_block2(m, add(m->plr.p, mv)) == '1')
		clip_x(m, block);
	else
		m->plr.p = add(m->plr.p, mv);
}

void	check_collision(t_main *m)
{
	int		i;
	t_vecf	blocks[9];

	fill_block_pos(m, blocks);
	i = 0;
	while (i < 9)
	{
		if (get_block2(m, blocks[i]) == '1' && absf(sub(blocks[i], m->plr.p).x) < COLLISION_DIST
			&& absf(sub(blocks[i], m->plr.p).x) >= absf(sub(blocks[i], m->plr.p).y))
			clip_x(m, blocks[i]);
		if (get_block2(m, blocks[i]) == '1' && absf(sub(blocks[i], m->plr.p).y) < COLLISION_DIST
			&& absf(sub(blocks[i], m->plr.p).y) >= absf(sub(blocks[i], m->plr.p).x))
			clip_y(m, blocks[i]);
		i++;
	}
}