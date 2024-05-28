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

void	free_map(void *mlxptr, t_map *m)
{
	free_txr(mlxptr, &(m->n));
	free_txr(mlxptr, &(m->s));
	free_txr(mlxptr, &(m->e));
	free_txr(mlxptr, &(m->w));
}

void	free_main(t_main *main)
{
	free_map(main->mlxptr, &(main->map));
}
