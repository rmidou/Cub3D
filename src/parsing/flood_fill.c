#include "../../includes/cub3D.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	flood(char **map, t_veci s, t_veci p)
{
	if (p.x < 0 || p.x >= s.x
		|| p.y < 0 || p.y >= s.y
		|| map[p.y][p.x] == '\0'
		|| map[p.y][p.x] == ' ')
		return (1);
	if (map[p.y][p.x] == '1')
		return (0);
	map[p.y][p.x] = '1';
	return (flood(map, s, (t_veci){p.x + 1, p.y})
		+ flood(map, s, (t_veci){p.x - 1, p.y})
		+ flood(map, s, (t_veci){p.x, p.y + 1})
		+ flood(map, s, (t_veci){p.x, p.y - 1}));
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("|%s|\n", tab[i]);
		i++;
	}
}

int	flood_fill(t_map *m)
{
	int		out;
	t_veci	pos;
	char	**map;

	get_map_specs(m);
	pos = m->spawn;
	map = ft_split(m->data, '\n');
	out = flood(map, m->size, pos) > 0;
	free_split(map);
	return (out);
}
