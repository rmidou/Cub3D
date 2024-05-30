
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

# define RED_PIXEL	0xFF0000
# define BLACK_PIXEL 0x000000
# define WHITE_PIXEL 0xFFFFFF
# define BLUE_PIXEL	0x77B5FE
# define PI			3.141592f
# define OFFSET		-0.f

# define CEIL	0
# define FLOOR	1
# define X_		0
# define Y_		1

# define HIT_N	0
# define HIT_S	1
# define HIT_E	2
# define HIT_W	3

# define MAP_CHARS	" 10NSEW"

# define LN_TYPE_EMPTY		0
# define LN_TYPE_TXR		1
# define LN_TYPE_CLR		2
# define LN_TYPE_MAP		3
# define LN_TYPE_UNDEF		4

# define OKAY_OKAY				0
# define ERR_OPEN				1
# define ERR_NOFILE				2
# define ERR_LOADTEX			3
# define ERR_NOCLR				4
# define ERR_SYNTAX				5
# define ERR_NO_DATA_EXPECTED	6
# define ERR_UNKNOWN			7
# define ERR_OUT_OF_BOUNDS		8
# define ERR_PARSING			9

# define STAGE_DATA	0
# define STAGE_MAP	1
# define STAGE_DONE	2

# define SCREEN_W		1920.f
# define SCREEN_H		1080.f
# define FOV 			90.f
# define RENDER_DIST	8.f
# define SCREEN_DIST	1.f
# define COL_W			1
# define SPEED			0.25f
# define SCREEN_SIZE	64.f

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
	int		hit;
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
int		move(int key, t_main *map);
int		rgb(int t, int r, int g, int b);

/*		map.c	*/
void	free_main(t_main *main);
char	get_block2(t_main *main, t_vecf p);

/*		img.c	*/
void	draw_line(t_main *main, t_veci start, t_veci end, int color);
void	reset_screen(t_main *main);
t_clr	get_pixel(t_txr t, int x, int y);
void	set_pixel(int color, t_txr t, int x, int y);

/*		draw_rays.c	*/
void	draw_rays(t_main *map);
void	draw_line(t_main *main, t_veci start, t_veci end, int color);
void	shoot_rays(t_main *main);
char	get_block(t_main *main, t_ray r);

/*		textures.c	*/
void	draw_texture(t_main *m, int x_pos, t_ray r);

/*		parsing.c	*/
int		build_map(void *mlx_ptr, t_map *m, char *file);

/*		parsing2.c	*/
int		read_mapline(t_map *m, char *line);
int		read_color(t_map *m, char *line);
int		read_texture(void *mlx_ptr, t_map *m, char *line);

/*		error.c		*/
int		max(int i1, int i2);
int		throw_error(int err, char *line);
void	print_map(t_map *map);

/*		ray.c		*/
void	whey(t_ray *ray);
float	dist(t_vecf v);
void	init_dir(t_ray *r);
void	init_dir2(t_ray *r);

/*		color.c		*/
t_clr	color(int r, int g, int b);
t_clr	get_hit_color(t_main *m, t_ray r);
t_clr	scale_clr(t_clr c, float f);

/*		angles.c	*/
t_vecf	ang_to_vecf(float a);
float	fix_ang(float a);
float	to_rad(float a);
float	to_deg(float a);
t_vecf	rotate(t_vecf v, float a);

/*		vectors.c	*/
t_vecf	vecf(float x, float y);
float	dist(t_vecf v);
t_vecf	norm(t_vecf v);
t_vecf	add(t_vecf u, t_vecf v);
t_vecf	sub(t_vecf u, t_vecf v);

/*		vectors2.c	*/
t_vecf	scale(t_vecf v, float f);
int		get_line_height(t_main *m, t_ray r);

void	mini_map(t_main *main);

#endif
