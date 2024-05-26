#include "../includes/cub3D.h"

int	load_tex(void *mlx_ptr, t_txr *t)
{
	t->img = mlx_xpm_file_to_image(mlx_ptr, t->file, &(t->size.x), &(t->size.y));
	if (t->img == NULL)
		return (ERR_LOADTEX);
	t->data = mlx_get_data_addr(t->img, &(t->bpp), &(t->line), &(t->endian));
	return (OKAY_OKAY);
}

int	read_texture(void *mlx_ptr, t_map *m, char *line)
{
	t_txr	*t;
	int		i;

	i = 2;
	if (line[0] == 'N')
		t = &(m->n);
	if (line[0] == 'S')
		t = &(m->s);
	if (line[0] == 'E')
		t = &(m->e);
	if (line[0] == 'W')
		t = &(m->w);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (ERR_NOFILE);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	t->file = str_adds(NULL, line, ft_strlen(line));
	return (load_tex(mlx_ptr, t));
}

int read_color_data(t_clr *c, char *line)
{
	int	i;

	i = 0;
	c->r = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (ERR_SYNTAX);
	c->g = ft_atoi(&(line[++i]));
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (ERR_SYNTAX);
	c->b = ft_atoi(&(line[++i]));
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (ERR_SYNTAX);
	c->color_i = 0xFFFFFF & ((char)c->r << 24 | (char)c->g << 16 | (char)c->r << 8);
	if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255 || c->b < 0 || c->b > 255)
		return (ERR_OUT_OF_BOUNDS);
	return (OKAY_OKAY);
}

int	read_color(t_map *m, char *line)
{
	t_clr	*c;
	int		i;

	i = 1;
	if (line[0] == 'F')
		c = &(m->floor);
	if (line[0] == 'C')
		c = &(m->ceiling);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (ERR_NOCLR);
	return (read_color_data(c, &(line[i])));
}

int	read_mapline(t_map *m, char *line)
{
	m->data = str_adds(m->data, line, ft_strlen(line));
	return (OKAY_OKAY);
}