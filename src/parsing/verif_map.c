#include "../../includes/cub3D.h"

int	verif_color_line(t_clr *c, char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ',')
			commas++;
		else if (!ft_isdigit(line[i])
			&& line[i] != ' ' && line[i] != '\t')
			return (ERR_SYNTAX);
		i++;
	}
	if (commas != 2)
		return (ERR_SYNTAX);
	return (read_color_data(c, line));
}

int	verif_textures(t_map *m)
{
	if (m->n.txrs[0].file == NULL
		|| m->s.txrs[0].file == NULL
		|| m->e.txrs[0].file == NULL
		|| m->w.txrs[0].file == NULL)
		return (ERR_MISSING_TEX);
	return (OKAY_OKAY);
}