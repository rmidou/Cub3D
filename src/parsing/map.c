#include "../../includes/cub3D.h"

char	get_block2(t_main *main, t_vecf p)
{
	t_veci	i;

	i.x = (int)floorf(p.x);
	i.y = (int)floorf(p.y);
	if (i.y < 0.f || i.y >= main->map.size.y
		|| i.x < 0.f || i.x >= main->map.size.x)
		return ('1');
	return (main->map.map[i.y][i.x]);
}

void	free2(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
}

void	free_txr(void *mlxptr, t_txr *t)
{
	free2(t->file);
	if (t->img != NULL)
		mlx_destroy_image(mlxptr, t->img);
	ft_bzero(t, sizeof(t));
}

void	free_map2(t_map *m)
{
	int	i;

	i = 0;
	while (m->map[i])
	{
		free(m->map[i]);
		i++;
	}
	free(m->map);
}

void	free_map(void *mlxptr, t_map *m)
{
	free_txr(mlxptr, &(m->n.txrs[0]));
	free2(m->n.txrs);
	free_txr(mlxptr, &(m->s.txrs[0]));
	free2(m->s.txrs);
	free_txr(mlxptr, &(m->e.txrs[0]));
	free2(m->e.txrs);
	free_txr(mlxptr, &(m->w.txrs[0]));
	free2(m->w.txrs);
	free2(m->d.txrs);
	free_map2(m);
	free2(m->data);
	free2(m->file);
}

void	free_main(t_main *main)
{
	free_map(main->mlxptr, &(main->map));
}
