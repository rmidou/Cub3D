#include "../includes/cub3D.h"

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
	while (ft_strchr(MAP_CHARS, line[i]) != NULL)
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (LN_TYPE_MAP);
	return (LN_TYPE_UNDEF);
}

int	parse_line(char *line, t_map *m)
{
	ft_printf("%d\n", get_line_type(line));
}

int	build_map(t_map *m, char *file)
{
	int	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN);
	while (1)
	{
		line = get_next_line(fd);
	}
	
}
