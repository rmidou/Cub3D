#include "../includes/cub3D.h"

void	free_map(t_main *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	i = 0;
	while (map->buf[i])
	{
		free(map->buf[i]);
		i++;
	}
	free(map->buf);
}

void	print_map(t_main *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (map->map[y])
	{
		i = 0;
		while (map->map[y][i])
		{
			map->x = i;
			map->y = y;
			put_img(map->map[y][i], *map);
			i++;
		}
		y++;
	}
}

void	nb_ligne(t_main *map, char *av)
{
	int		i;
	char	*ligne;

	ligne = get_next_line(map->fd);
	free(ligne);
	i = 0;
	while (ligne)
	{
		ligne = get_next_line(map->fd);
		free(ligne);
		i++;
	}
	if (map->fd != -1)
		close(map->fd);
	map->fd = open(av, O_RDONLY);
	map->heightmap = i;
}

int	read_map(t_main *map, char *av)
{
	char	*ligne;
	int		y;

	y = 0;
	if (av == NULL)
		return (0);
	map->fd = open(av, O_RDONLY);
	nb_ligne(map, av);
	ligne = get_next_line(map->fd);
	map->map = malloc(sizeof(char *) * (map->heightmap + 1));
	map->buf = malloc(sizeof(char *) * (map->heightmap + 1));
	while (ligne)
	{
		map->map[y] = ligne;
		map->buf[y] = ft_strdup(ligne);
		ligne = get_next_line(map->fd);
		y++;
	}
	map->map[y] = NULL;
	map->buf[y] = NULL;
	if (map->fd != -1)
		close(map->fd);
	return (1);
}
