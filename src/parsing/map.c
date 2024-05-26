#include "../../includes/cub3D.h"

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
