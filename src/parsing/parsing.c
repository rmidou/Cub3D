#include "../../includes/cub3D.h"

int	get_line_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (LN_TYPE_EMPTY);
	if ((line[0] == 'N' && line[1] == 'O')
	||	(line[0] == 'S' && line[1] == 'O')
	||	(line[0] == 'E' && line[1] == 'A')
	||	(line[0] == 'W' && line[1] == 'E'))
		return (LN_TYPE_TXR);
	if (line[0] == 'F'
	||	line[0] == 'C')
		return (LN_TYPE_CLR);
	i = 0;
	while (line[i] && ft_strchr(MAP_CHARS, line[i]) != NULL)
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (LN_TYPE_MAP);
	return (LN_TYPE_UNDEF);
}

int	parse_line(void *mlx_ptr, char *line, int *stage, t_map *m)
{
	int	out;

	out = get_line_type(line);
	if (out == LN_TYPE_UNDEF)
		return (ERR_UNKNOWN);
	if (*stage == STAGE_DONE && out != LN_TYPE_EMPTY)
		return (ERR_NO_DATA_EXPECTED);
	if (*stage == STAGE_MAP && out != LN_TYPE_MAP && out != LN_TYPE_EMPTY)
		return (ERR_NO_DATA_EXPECTED);
	if (*stage == STAGE_MAP && out == LN_TYPE_EMPTY)
		*stage = STAGE_DONE;
	if (*stage == STAGE_DATA && out == LN_TYPE_MAP)
		*stage = STAGE_MAP;
	if (out == LN_TYPE_EMPTY)
		return (OKAY_OKAY);
	if (out == LN_TYPE_TXR)
		return (read_texture(mlx_ptr, m, line));
	if (out == LN_TYPE_CLR)
		return (read_color(m, line));
	if (out == LN_TYPE_MAP)
		return (read_mapline(m, line));
	return (ERR_UNKNOWN);
}

void	get_spawn(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->size.y)
	{
		x = 0;
		while (x < m->size.x)
		{
			if (ft_strchr("NSEW", m->map[y][x]) != NULL && m->map[y][x])
				m->spawn = (t_veci){x, y};
			x++;
		}
		y++;
	}
	if (m->map[m->spawn.y][m->spawn.x] == 'N')
		m->view = 270;
	if (m->map[m->spawn.y][m->spawn.x] == 'S')
		m->view = 90;
	if (m->map[m->spawn.y][m->spawn.x] == 'E')
		m->view = 0;
	if (m->map[m->spawn.y][m->spawn.x] == 'W')
		m->view = 180;
}

void	get_map_specs(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (m->map[y])
	{
		x = max(x, ft_strlen(m->map[y]));
		y++;
	}
	m->size = (t_veci){.x = x, .y = y};
	y = 0;
	while (m->map[y])
	{
		while (ft_strlen(m->map[y]) < x)
			m->map[y] = str_addc(m->map[y], ' ');
		y++;
	}
	get_spawn(m);
}

int	build_map(void *mlx_ptr, t_map *m, char *file)
{
	int		fd;
	int		stage;
	char	*line;
	int		err;

	err = 0;
	stage = STAGE_DATA;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN);
	while (!err)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		err = throw_error(parse_line(mlx_ptr, line, &stage, m), line);
		free(line);
	}
	close(fd);
	if (err)
		return (ERR_PARSING);
	m->map = ft_split(m->data, '\n');
	get_map_specs(m);
	return (OKAY_OKAY);
}
