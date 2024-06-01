#include "../../includes/cub3D.h"

void	update_textures(t_anim *t)
{
	t->frame = (t->frame + 1) % t->size;
}

int	init_animation(t_anim *t, int frames)
{
	t->txrs = malloc(sizeof(t_txr) * frames);
	t->size = frames;
	return (1);
}

void	init_texture(t_main *m)
{
	init_animation(&m->map.n, 2);
	init_animation(&m->map.s, 1);
	init_animation(&m->map.e, 1);
	init_animation(&m->map.w, 1);
	init_animation(&m->map.d, 1);
	m->map.d.frame = 0;
	m->map.d.txrs->file = "textures/door.xpm";
	load_tex(m->mlxptr, &m->map.d.txrs[0]);
}
