
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
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
#define	OFFSET		-0.f

#define CEIL	0
#define FLOOR	1
#define X_		0
#define Y_		1

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
#define RENDER_DIST	30.f
#define SCREEN_DIST	.25f
#define AR			((float)SCREEN_W / (float)SCREEN_H)
#define SW			((float)SCREEN_DIST / tanf(deg_to_rad(90.f - (FOV / 2.f))))
#define SH			(SW / AR)
#define COL_W		10
#define	SPEED		0.1f
#define SCREEN_SIZE	64.f

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

typedef struct s_ray
{
	int		index;
	float	a;
	t_vecf	p;
	t_vecf	d;
	t_vecf	n;
	t_vecf	dx;
	t_vecf	dy;
}	t_ray;

typedef struct s_main
{
	t_ray	plr;

	t_map	map;

	t_txr	scr;

	void	*mlxptr;
	void	*winptr;
}	t_main;

/*		main.c	*/
int		on_destroy(t_main *map);

/*		move.c	*/
float	deg_to_rad(float a);
float	rad_to_deg(float a);
int		move(int key, t_main *map);
float	fix_ang(float a);
int	rgb(int t, int r, int g, int b);

/*		map.c	*/
void	free_main(t_main *main);

/*		img.c	*/

/*		draw_rays.c	*/
void	draw_rays(t_main *map);
void	draw_line(t_main *main, t_veci start, t_veci end, int color);
void    draw_view_line(t_main *main);
char	get_block(t_main *main, t_ray r);

void	set_pixel(int color, t_txr t, int x, int y);

/*		parsing.c	*/
int	build_map(void *mlx_ptr, t_map *m, char *file);

/*		parsing2.c	*/
int	read_mapline(t_map *m, char *line);
int	read_color(t_map *m, char *line);
int	read_texture(void *mlx_ptr, t_map *m, char *line);

/*		error.c		*/
int	max(int i1, int i2);
int	throw_error(int err, char *line);
void	print_map(t_map *map);

/*		ray.c		*/
void	whey(t_ray *ray);
float	dist(t_vecf v);
void	init_dir(t_ray *r);
void	init_dir2(t_ray *r);

#endif
