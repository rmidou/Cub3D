
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>

#define RED_PIXEL	0xFF0000
#define BLACK_PIXEL 0x000000
#define WHITE_PIXEL 0xFFFFFF
#define BLUE_PIXEL	0x77B5FE
#define PI			3.141592f

#define MAP_CHARS	" 10NSEW"

#define	LN_TYPE_EMPTY	0
#define LN_TYPE_TXR		1
#define LN_TYPE_CLR		2
#define LN_TYPE_MAP		3
#define LN_TYPE_UNDEF	4

#define OKAY_OKAY				0
#define ERR_OPEN				1
#define ERR_NOFILE				2
#define ERR_LOADTEX				3
#define ERR_NOCLR				4
#define ERR_SYNTAX				5
#define ERR_NO_DATA_EXPECTED	6
#define ERR_UNKNOWN				7
#define ERR_OUT_OF_BOUNDS		8
#define ERR_PARSING				9

#define STAGE_DATA	0
#define STAGE_MAP	1
#define STAGE_DONE	2

#define SCREEN_W	1920
#define SCREEN_H	1280
#define FOV 		90
#define	SPEED		10

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;


typedef struct s_txr
{
	char			*file;
	char			*data;
	void			*img;
	int				bpp;
	int				line;
	int				endian;
	t_veci			size;
}	t_txr;

typedef struct s_vecf
{
	float	x;
	float	y;
}	t_vecf;

typedef struct s_clr
{
	int	r;
	int	g;
	int	b;
	int	color_i;
}	t_clr;

typedef struct s_map
{
	char	*file;
	char	*data;
	char	**map;
	t_veci	size;
	t_veci	spawn;
	float	view;
	t_txr	n;
	t_txr	s;
	t_txr	e;
	t_txr	w;
	t_clr	floor;
	t_clr	ceiling;
}	t_map;

typedef struct s_main
{
	int		x;
	int		y;
	int		px;
	int		py;
	float		pa;
	float		dx;
	float		dy;
	float		fd;

	t_map	map;

	t_txr	scr;

	void	*mlxptr;
	void	*winptr;
}	t_main;

/*		main.c	*/
int		on_destroy(t_main *map);

/*		move.c	*/
float	deg_to_rad(float a);
int		move(int key, t_main *map);
int		fix_ang(int a);

/*		map.c	*/
void	free_map(t_main *map);
int		read_map(t_main *map, char *av);

/*		img.c	*/

/*		draw_rays.c	*/
void	draw_rays(t_main *map);
int		draw_line(t_main *main, int x0, int y0, int x1, int y1, int color);
void    draw_view_line(t_main *main);

void	set_pixel(int color, void *img, int x, int y);

/*		parsing.c	*/
int	build_map(void *mlx_ptr, t_map *m, char *file);

/*		parsing2.c	*/
int	read_mapline(t_map *m, char *line);
int	read_color(t_map *m, char *line);
int	read_texture(void *mlx_ptr, t_map *m, char *line);

/*		error.c		*/
int	max(int i1, int i2);
int	throw_error(int err, char *line);

#endif
