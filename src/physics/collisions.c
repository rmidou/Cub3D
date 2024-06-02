#include "../../includes/cub3D.h"

void	fill_block_pos(t_main *m, t_vecf blocks[9])
{
	blocks[0] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f,
		.y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[1] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f,
		.y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[2] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f,
		.y = floorf(m->plr.p.y - 1.f) + .5f};
	blocks[3] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f,
		.y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[4] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f,
		.y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[5] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f,
		.y = floorf(m->plr.p.y - 0.f) + .5f};
	blocks[6] = (t_vecf){.x = floorf(m->plr.p.x - 1.f) + .5f,
		.y = floorf(m->plr.p.y + 1.f) + .5f};
	blocks[7] = (t_vecf){.x = floorf(m->plr.p.x - 0.f) + .5f,
		.y = floorf(m->plr.p.y + 1.f) + .5f};
	blocks[8] = (t_vecf){.x = floorf(m->plr.p.x + 1.f) + .5f,
		.y = floorf(m->plr.p.y + 1.f) + .5f};
}

void	clip_x(t_main *m, t_vecf block, char c, int stop)
{
	t_vecf	mv;

	mv.y = 0;
	if (sub(block, m->plr.p).x < 0)
		mv.x = COLLISION_DIST - absf(sub(block, m->plr.p).x);
	else
		mv.x = -(COLLISION_DIST - absf(sub(block, m->plr.p).x));
	if (get_block2(m, add(m->plr.p, scale(mv, 2.f))) == c && !stop)
		clip_y(m, block, c, 1);
	else
		m->plr.p = add(m->plr.p, scale(mv, 2.f));
}

void	clip_y(t_main *m, t_vecf block, char c, int stop)
{
	t_vecf	mv;

	mv.x = 0;
	if (sub(block, m->plr.p).y < 0)
		mv.y = COLLISION_DIST - absf(sub(block, m->plr.p).y);
	else
		mv.y = -(COLLISION_DIST - absf(sub(block, m->plr.p).y));
	if (get_block2(m, add(m->plr.p, scale(mv, 2.f))) == c && !stop)
		clip_x(m, block, c, 1);
	else
		m->plr.p = add(m->plr.p, scale(mv, 2.f));
}

int	check_collision2(t_main *m, char c, t_vecf blocks[9], int i)
{
	return (get_block2(m, blocks[i]) == c
		&& absf(sub(blocks[i], m->plr.p).x) < COLLISION_DIST
		&& absf(sub(blocks[i], m->plr.p).x)
		>= absf(sub(blocks[i], m->plr.p).y));
}

void	check_collision(t_main *m)
{
	int		i;
	t_vecf	blocks[9];

	fill_block_pos(m, blocks);
	i = 0;
	while (i < 9)
	{
		if (check_collision2(m, '1', blocks, i))
			clip_x(m, blocks[i], '1', 0);
		if (check_collision2(m, 'D', blocks, i))
			clip_x(m, blocks[i], 'D', 0);
		if (get_block2(m, blocks[i]) == '1'
			&& absf(sub(blocks[i], m->plr.p).y) < COLLISION_DIST
			&& absf(sub(blocks[i], m->plr.p).y)
			>= absf(sub(blocks[i], m->plr.p).x))
			clip_y(m, blocks[i], '1', 0);
		if (get_block2(m, blocks[i]) == 'D'
			&& absf(sub(blocks[i], m->plr.p).y) < COLLISION_DIST
			&& absf(sub(blocks[i], m->plr.p).y)
			>= absf(sub(blocks[i], m->plr.p).x))
			clip_y(m, blocks[i], 'D', 0);
		i++;
	}
}
