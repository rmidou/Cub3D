
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

#define OK			0
#define ERR_OPEN	1

#define SCREEN_W	1920
#define SCREEN_H	1280
#define FOV 		90

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
	int		widhtmap;
	int		heightmap;
	
	char	**map;
	char	**buf;

	void	*img;
	char	*scr_data;
	int		bpp;
	int		line;
	int		endian;

	void	*mlxptr;
	void	*winptr;
	void	*black;
	void	*white;
	void	*blue;
	void	*little_black;
	void	*little_white;

}	t_main;

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;

typedef struct s_vecf
{
	float	x;
	float	y;
}	t_vecf;

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

typedef struct s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				color_i;
	char			color_c[4];
}	t_clr;

typedef struct s_map
{
	char	*file;
	char	*data;
	t_veci	size;
	t_veci	spawn;
	float	view;
	t_txr	n;
	t_txr	s;
	t_txr	e;
	t_txr	w;
	t_clr	floor;
	t_clr	cieling;
}	t_map;

/*		main.c	*/
int		on_destroy(t_main *map);

/*		move.c	*/
float	deg_to_rad(float a);
int		move(int key, t_main *map);
int		fix_ang(int a);

/*		map.c	*/
void	free_map(t_main *map);
void	print_map(t_main *map);
int		read_map(t_main *map, char *av);

/*		img.c	*/
void	init_img(t_main *map);
void	put_(t_main *map);
void	put_img(char chara, t_main map);

/*		draw_rays.c	*/
void	draw_rays(t_main *map);
int		draw_line(t_main *main, int x0, int y0, int x1, int y1, int color);
void    draw_view_line(t_main *main);

void	set_pixel(int color, void *img, int x, int y);
#endif
